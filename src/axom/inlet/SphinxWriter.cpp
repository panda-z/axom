// Copyright (c) 2017-2021, Lawrence Livermore National Security, LLC and
// other Axom Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (BSD-3-Clause)

/*!
 *******************************************************************************
 * \file SphinxWriter.cpp
 *
 * \brief This file contains the class implementation of the SphinxWriter.
 *******************************************************************************
 */

#include "axom/inlet/SphinxWriter.hpp"

#include <iostream>

#include "axom/slic.hpp"
#include "axom/inlet/Table.hpp"

namespace axom
{
namespace inlet
{
SphinxWriter::SphinxWriter(const std::string& fileName, bool outputProvidedValues)
  : m_fieldColLabels({"Field Name",
                      "Description",
                      "Default Value",
                      "Range/Valid Values",
                      "Required"})
  , m_functionColLabels(
      {"Function Name", "Description", "Signature", "Required"})
{
  m_fileName = fileName;

  if(outputProvidedValues)
  {
    // The value provided by the user in the input file
    m_fieldColLabels.push_back("Value");
  }

  m_oss << ".. |uncheck|    unicode:: U+2610 .. UNCHECKED BOX\n";
  m_oss << ".. |check|      unicode:: U+2611 .. CHECKED BOX\n\n";
  writeTitle("Input file Options");
}

void SphinxWriter::documentTable(const Table& table)
{
  const auto sidreGroup = table.sidreGroup();
  const std::string pathName = sidreGroup->getPathName();
  std::string tableName = sidreGroup->getName();
  bool isSelectedElement = false;

  if(tableName == detail::CONTAINER_GROUP_NAME)
  {
    tableName = "Container contents:";
  }

  // Avoid duplicating schema tables by selecting a single element to display
  // By keeping track of these selections, this logic extends to subtrees
  for(const auto& selection : m_selectedElements)
  {
    std::string selectedElement =
      appendPrefix(selection.first, detail::CONTAINER_GROUP_NAME);
    selectedElement = appendPrefix(selectedElement, selection.second);
    // If we *are* part of an array/dict for which an element is selected,
    // but we *are not* the selected element, bail out
    if((pathName.find(selection.first) != std::string::npos) &&
       (pathName.find(selectedElement) == std::string::npos))
    {
      return;
    }
  }

  // If we've gotten to this point and are an element of an array/dict,
  // mark it as the selected element
  if(sidreGroup->hasView(detail::CONTAINER_ELEMENT_FLAG))
  {
    // The container that this Table is a part of
    const std::string containerName =
      sidreGroup->getParent()->getParent()->getPathName();
    m_selectedElements.push_back({containerName, tableName});
    isSelectedElement = true;
  }

  m_inletTablePathNames.push_back(pathName);
  auto& currTable =
    m_rstTables
      .emplace(pathName, TableData {m_fieldColLabels, m_functionColLabels})
      .first->second;
  currTable.tableName = tableName;
  currTable.isSelectedElement = isSelectedElement;
  if(tableName != "" && sidreGroup->hasView("description"))
  {
    currTable.description = sidreGroup->getView("description")->getString();
  }

  for(const auto& field_entry : table.getChildFields())
  {
    extractFieldMetadata(field_entry.second->sidreGroup(), currTable);
  }

  for(const auto& function_entry : table.getChildFunctions())
  {
    extractFunctionMetadata(function_entry.second->sidreGroup(), currTable);
  }
}

void SphinxWriter::finalize()
{
  writeAllTables();
  m_outFile.open(m_fileName);
  m_outFile << m_oss.str();
  m_outFile.close();
}

void SphinxWriter::writeTitle(const std::string& title)
{
  if(title != "")
  {
    std::string equals = std::string(title.length(), '=');
    m_oss << equals << "\n" << title << "\n" << equals << "\n";
  }
}

void SphinxWriter::writeSubtitle(const std::string& sub)
{
  if(sub != "")
  {
    std::string dashes = std::string(sub.length(), '-');
    m_oss << "\n" << dashes << "\n" << sub << "\n" << dashes << "\n\n";
  }
}

void SphinxWriter::writeTable(const std::string& title,
                              const std::vector<std::vector<std::string>>& rstTable)
{
  SLIC_WARNING_IF(
    rstTable.size() <= 1,
    "[Inlet] Vector for corresponding rst table must be nonempty");
  std::string result = ".. list-table:: " + title;
  std::string widths = ":widths:";
  // This would be easier with an iterator adaptor like back_inserter but for
  // concatenation
  for(std::size_t i = 0u; i < rstTable.front().size(); i++)
  {
    widths += " 25";
  }
  result += "\n   " + widths + "\n";
  result += "   :header-rows: 1\n   :stub-columns: 1\n\n";
  for(unsigned int i = 0; i < rstTable.size(); ++i)
  {
    result += "   * - ";
    for(unsigned int j = 0; j < rstTable[i].size(); ++j)
    {
      if(j != 0)
      {
        result += "     - ";
      }
      result += rstTable[i][j] + "\n";
    }
  }
  m_oss << result;
}

void SphinxWriter::writeAllTables()
{
  for(std::string& pathName : m_inletTablePathNames)
  {
    auto& currTable = m_rstTables.at(pathName);
    // If we're displaying a selected element, the title and description
    // will already have been printed
    if(currTable.isSelectedElement)
    {
      m_oss << "The input schema defines an array of this table.\n";
      m_oss << "For brevity, only one instance is displayed here.\n\n";
    }
    else
    {
      writeSubtitle(currTable.tableName);
      if(currTable.description != "")
      {
        m_oss << "Description: " << currTable.description << "\n\n";
      }
    }
    if(currTable.fieldTable.size() > 1)
    {
      writeTable("Fields", currTable.fieldTable);
    }
    if(currTable.functionTable.size() > 1)
    {
      writeTable("Functions", currTable.functionTable);
    }
  }
}

std::string SphinxWriter::getValueAsString(const axom::sidre::View* view)
{
  axom::sidre::TypeID type = view->getTypeID();
  if(type == axom::sidre::TypeID::INT8_ID)
  {
    int8 val = view->getData();
    return val ? "True" : "False";
  }
  else if(type == axom::sidre::TypeID::INT_ID)
  {
    int val = view->getData();
    return std::to_string(val);
  }
  else if(type == axom::sidre::TypeID::DOUBLE_ID)
  {
    double val = view->getData();
    return std::to_string(val);
  }
  return view->getString();
}

std::string SphinxWriter::getRangeAsString(const axom::sidre::View* view)
{
  std::ostringstream oss;
  oss.precision(3);
  oss << std::scientific;

  axom::sidre::TypeID type = view->getTypeID();
  if(type == axom::sidre::INT_ID)
  {
    const int* range = view->getData();
    oss << range[0] << " to " << range[1];
  }
  else
  {
    const double* range = view->getData();
    oss << range[0] << " to " << range[1];
  }
  return oss.str();
}

std::string SphinxWriter::getValidValuesAsString(const axom::sidre::View* view)
{
  const int* range = view->getData();
  size_t size = view->getBuffer()->getNumElements();
  std::string result = "";
  for(size_t i = 0; i < size; ++i)
  {
    if(i == size - 1)
    {
      result += std::to_string(range[i]);
    }
    else
    {
      result += std::to_string(range[i]) + ", ";
    }
  }
  return result;
}

std::string SphinxWriter::getValidStringValues(const axom::sidre::Group* sidreGroup)
{
  auto idx = sidreGroup->getFirstValidViewIndex();
  std::string validValues = "";
  while(axom::sidre::indexIsValid(idx))
  {
    validValues += std::string(sidreGroup->getView(idx)->getString());
    idx = sidreGroup->getNextValidViewIndex(idx);
    if(axom::sidre::indexIsValid(idx))
    {
      validValues += ", ";
    }
  }
  return validValues;
}

void SphinxWriter::extractFieldMetadata(const axom::sidre::Group* sidreGroup,
                                        TableData& currentTable)
{
  std::vector<std::string> fieldAttributes(m_fieldColLabels.size());

  fieldAttributes[0] = sidreGroup->getName();

  if(sidreGroup->hasView("description"))
  {
    fieldAttributes[1] =
      std::string(sidreGroup->getView("description")->getString());
  }

  if(sidreGroup->hasView("defaultValue"))
  {
    fieldAttributes[2] = getValueAsString(sidreGroup->getView("defaultValue"));
  }

  if(sidreGroup->hasView("range"))
  {
    fieldAttributes[3] = getRangeAsString(sidreGroup->getView("range"));
  }
  else if(sidreGroup->hasView("validValues"))
  {
    fieldAttributes[3] =
      getValidValuesAsString(sidreGroup->getView("validValues"));
  }
  else if(sidreGroup->hasGroup("validStringValues"))
  {
    fieldAttributes[3] =
      getValidStringValues(sidreGroup->getGroup("validStringValues"));
  }

  if(sidreGroup->hasView("required"))
  {
    int8 required = sidreGroup->getView("required")->getData();
    fieldAttributes[4] = required ? "|check|" : "|uncheck|";
  }
  else
  {
    fieldAttributes[4] = "|uncheck|";
  }

  // FIXME: Better to use an associative container here if the column header
  // set is variable?
  const auto& labels = currentTable.fieldTable.front();
  auto iter = std::find(labels.begin(), labels.end(), "Value");
  if(iter != labels.end())
  {
    const auto pos = std::distance(labels.begin(), iter);
    if(sidreGroup->hasView("value"))
    {
      fieldAttributes[pos] = getValueAsString(sidreGroup->getView("value"));
    }
    else
    {
      // Could also just leave it blank here?
      fieldAttributes[pos] = "N/A";
    }
  }

  currentTable.fieldTable.push_back(fieldAttributes);
}

std::string SphinxWriter::getSignatureAsString(const axom::sidre::Group* sidreGroup)
{
  const std::string retType = sidreGroup->getView("return_type")->getString();

  const sidre::Group* argsGroup = sidreGroup->getGroup("function_arguments");
  std::string argTypes;
  auto idx = argsGroup->getFirstValidViewIndex();
  while(axom::sidre::indexIsValid(idx))
  {
    argTypes += std::string(argsGroup->getView(idx)->getString());
    idx = argsGroup->getNextValidViewIndex(idx);
    if(axom::sidre::indexIsValid(idx))
    {
      argTypes += ", ";
    }
  }

  return fmt::format("{0}({1})", retType, argTypes);
}

void SphinxWriter::extractFunctionMetadata(const axom::sidre::Group* sidreGroup,
                                           TableData& currentTable)
{
  std::vector<std::string> functionAttributes(m_functionColLabels.size());

  functionAttributes[0] = sidreGroup->getName();

  if(sidreGroup->hasView("description"))
  {
    functionAttributes[1] =
      std::string(sidreGroup->getView("description")->getString());
  }

  functionAttributes[2] = getSignatureAsString(sidreGroup);

  if(sidreGroup->hasView("required"))
  {
    int8 required = sidreGroup->getView("required")->getData();
    functionAttributes[3] = required ? "|check|" : "|uncheck|";
  }
  else
  {
    functionAttributes[3] = "|uncheck|";
  }

  currentTable.functionTable.push_back(functionAttributes);
}

}  // namespace inlet
}  // namespace axom
