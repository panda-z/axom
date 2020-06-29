! wrapfspio.f
! This is generated code, do not edit
!
! Copyright (c) 2017-2020, Lawrence Livermore National Security, LLC and
! other Axom Project Developers. See the top-level COPYRIGHT file for details.
!
! SPDX-License-Identifier: (BSD-3-Clause)
!>
!! \file wrapfspio.f
!! \brief Shroud generated wrapper for sidre namespace
!<
! splicer begin file_top
! splicer end file_top
module axom_spio
    use iso_c_binding, only : C_INT, C_NULL_PTR, C_PTR
    ! splicer begin module_use
    ! splicer end module_use
    implicit none

    ! splicer begin module_top
    ! splicer end module_top

    type, bind(C) :: SHROUD_iomanager_capsule
        type(C_PTR) :: addr = C_NULL_PTR  ! address of C++ memory
        integer(C_INT) :: idtor = 0       ! index of destructor
    end type SHROUD_iomanager_capsule

    type iomanager
        type(SHROUD_iomanager_capsule) :: cxxmem
        ! splicer begin class.IOManager.component_part
        ! splicer end class.IOManager.component_part
    contains
        procedure :: delete => iomanager_delete
        procedure :: write_0 => iomanager_write_0
        procedure :: write_1 => iomanager_write_1
        procedure :: write_group_to_root_file => iomanager_write_group_to_root_file
        procedure :: write_blueprint_index_to_root_file => iomanager_write_blueprint_index_to_root_file
        procedure :: read_0 => iomanager_read_0
        procedure :: read_1 => iomanager_read_1
        procedure :: read_2 => iomanager_read_2
        procedure :: read_3 => iomanager_read_3
        procedure :: read_4 => iomanager_read_4
        procedure :: load_external_data => iomanager_load_external_data
        procedure :: get_instance => iomanager_get_instance
        procedure :: set_instance => iomanager_set_instance
        procedure :: associated => iomanager_associated
        generic :: read => read_0, read_1, read_2, read_3, read_4
        generic :: write => write_0, write_1
        ! splicer begin class.IOManager.type_bound_procedure_part
        ! splicer end class.IOManager.type_bound_procedure_part
    end type iomanager

    interface operator (.eq.)
        module procedure iomanager_eq
    end interface

    interface operator (.ne.)
        module procedure iomanager_ne
    end interface

    interface

        function c_iomanager_new_0(com, SHT_crv) &
                result(SHT_rv) &
                bind(C, name="SPIO_IOManager_new_0")
            use iso_c_binding, only : C_INT, C_PTR
            import :: SHROUD_iomanager_capsule
            implicit none
            integer(C_INT), value, intent(IN) :: com
            type(SHROUD_iomanager_capsule), intent(OUT) :: SHT_crv
            type(C_PTR) SHT_rv
        end function c_iomanager_new_0

        function c_iomanager_new_1(com, use_scr, SHT_crv) &
                result(SHT_rv) &
                bind(C, name="SPIO_IOManager_new_1")
            use iso_c_binding, only : C_BOOL, C_INT, C_PTR
            import :: SHROUD_iomanager_capsule
            implicit none
            integer(C_INT), value, intent(IN) :: com
            logical(C_BOOL), value, intent(IN) :: use_scr
            type(SHROUD_iomanager_capsule), intent(OUT) :: SHT_crv
            type(C_PTR) SHT_rv
        end function c_iomanager_new_1

        subroutine c_iomanager_delete(self) &
                bind(C, name="SPIO_IOManager_delete")
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
        end subroutine c_iomanager_delete

        subroutine c_iomanager_write_0(self, group, num_files, &
                file_string, protocol) &
                bind(C, name="SPIO_IOManager_write_0")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            integer(C_INT), value, intent(IN) :: num_files
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            character(kind=C_CHAR), intent(IN) :: protocol(*)
        end subroutine c_iomanager_write_0

        subroutine c_iomanager_write_0_bufferify(self, group, num_files, &
                file_string, Lfile_string, protocol, Lprotocol) &
                bind(C, name="SPIO_IOManager_write_0_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            integer(C_INT), value, intent(IN) :: num_files
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            integer(C_INT), value, intent(IN) :: Lfile_string
            character(kind=C_CHAR), intent(IN) :: protocol(*)
            integer(C_INT), value, intent(IN) :: Lprotocol
        end subroutine c_iomanager_write_0_bufferify

        subroutine c_iomanager_write_1(self, group, num_files, &
                file_string, protocol, pattern) &
                bind(C, name="SPIO_IOManager_write_1")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            integer(C_INT), value, intent(IN) :: num_files
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            character(kind=C_CHAR), intent(IN) :: protocol(*)
            character(kind=C_CHAR), intent(IN) :: pattern(*)
        end subroutine c_iomanager_write_1

        subroutine c_iomanager_write_1_bufferify(self, group, num_files, &
                file_string, Lfile_string, protocol, Lprotocol, pattern, &
                Lpattern) &
                bind(C, name="SPIO_IOManager_write_1_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            integer(C_INT), value, intent(IN) :: num_files
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            integer(C_INT), value, intent(IN) :: Lfile_string
            character(kind=C_CHAR), intent(IN) :: protocol(*)
            integer(C_INT), value, intent(IN) :: Lprotocol
            character(kind=C_CHAR), intent(IN) :: pattern(*)
            integer(C_INT), value, intent(IN) :: Lpattern
        end subroutine c_iomanager_write_1_bufferify

        subroutine c_iomanager_write_group_to_root_file(self, group, &
                file_name) &
                bind(C, name="SPIO_IOManager_write_group_to_root_file")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: file_name(*)
        end subroutine c_iomanager_write_group_to_root_file

        subroutine c_iomanager_write_group_to_root_file_bufferify(self, &
                group, file_name, Lfile_name) &
                bind(C, name="SPIO_IOManager_write_group_to_root_file_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: file_name(*)
            integer(C_INT), value, intent(IN) :: Lfile_name
        end subroutine c_iomanager_write_group_to_root_file_bufferify

        subroutine c_iomanager_write_blueprint_index_to_root_file(self, &
                datastore, domain_path, file_name, mesh_path) &
                bind(C, name="SPIO_IOManager_write_blueprint_index_to_root_file")
            use axom_sidre, only : SHROUD_datastore_capsule
            use iso_c_binding, only : C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_datastore_capsule), intent(IN) :: datastore
            character(kind=C_CHAR), intent(IN) :: domain_path(*)
            character(kind=C_CHAR), intent(IN) :: file_name(*)
            character(kind=C_CHAR), intent(IN) :: mesh_path(*)
        end subroutine c_iomanager_write_blueprint_index_to_root_file

        subroutine c_iomanager_write_blueprint_index_to_root_file_bufferify( &
                self, datastore, domain_path, Ldomain_path, file_name, &
                Lfile_name, mesh_path, Lmesh_path) &
                bind(C, name="SPIO_IOManager_write_blueprint_index_to_root_file_bufferify")
            use axom_sidre, only : SHROUD_datastore_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_datastore_capsule), intent(IN) :: datastore
            character(kind=C_CHAR), intent(IN) :: domain_path(*)
            integer(C_INT), value, intent(IN) :: Ldomain_path
            character(kind=C_CHAR), intent(IN) :: file_name(*)
            integer(C_INT), value, intent(IN) :: Lfile_name
            character(kind=C_CHAR), intent(IN) :: mesh_path(*)
            integer(C_INT), value, intent(IN) :: Lmesh_path
        end subroutine c_iomanager_write_blueprint_index_to_root_file_bufferify

        subroutine c_iomanager_read_0(self, group, file_string, &
                protocol) &
                bind(C, name="SPIO_IOManager_read_0")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            character(kind=C_CHAR), intent(IN) :: protocol(*)
        end subroutine c_iomanager_read_0

        subroutine c_iomanager_read_0_bufferify(self, group, &
                file_string, Lfile_string, protocol, Lprotocol) &
                bind(C, name="SPIO_IOManager_read_0_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            integer(C_INT), value, intent(IN) :: Lfile_string
            character(kind=C_CHAR), intent(IN) :: protocol(*)
            integer(C_INT), value, intent(IN) :: Lprotocol
        end subroutine c_iomanager_read_0_bufferify

        subroutine c_iomanager_read_1(self, group, file_string, &
                protocol, preserve_contents) &
                bind(C, name="SPIO_IOManager_read_1")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_BOOL, C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            character(kind=C_CHAR), intent(IN) :: protocol(*)
            logical(C_BOOL), value, intent(IN) :: preserve_contents
        end subroutine c_iomanager_read_1

        subroutine c_iomanager_read_1_bufferify(self, group, &
                file_string, Lfile_string, protocol, Lprotocol, &
                preserve_contents) &
                bind(C, name="SPIO_IOManager_read_1_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_BOOL, C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: file_string(*)
            integer(C_INT), value, intent(IN) :: Lfile_string
            character(kind=C_CHAR), intent(IN) :: protocol(*)
            integer(C_INT), value, intent(IN) :: Lprotocol
            logical(C_BOOL), value, intent(IN) :: preserve_contents
        end subroutine c_iomanager_read_1_bufferify

        subroutine c_iomanager_read_2(self, group, root_file) &
                bind(C, name="SPIO_IOManager_read_2")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
        end subroutine c_iomanager_read_2

        subroutine c_iomanager_read_2_bufferify(self, group, root_file, &
                Lroot_file) &
                bind(C, name="SPIO_IOManager_read_2_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
            integer(C_INT), value, intent(IN) :: Lroot_file
        end subroutine c_iomanager_read_2_bufferify

        subroutine c_iomanager_read_3(self, group, root_file, &
                preserve_contents) &
                bind(C, name="SPIO_IOManager_read_3")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_BOOL, C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
            logical(C_BOOL), value, intent(IN) :: preserve_contents
        end subroutine c_iomanager_read_3

        subroutine c_iomanager_read_3_bufferify(self, group, root_file, &
                Lroot_file, preserve_contents) &
                bind(C, name="SPIO_IOManager_read_3_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_BOOL, C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
            integer(C_INT), value, intent(IN) :: Lroot_file
            logical(C_BOOL), value, intent(IN) :: preserve_contents
        end subroutine c_iomanager_read_3_bufferify

        subroutine c_iomanager_read_4(self, group, root_file, &
                preserve_contents, use_scr) &
                bind(C, name="SPIO_IOManager_read_4")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_BOOL, C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
            logical(C_BOOL), value, intent(IN) :: preserve_contents
            logical(C_BOOL), value, intent(IN) :: use_scr
        end subroutine c_iomanager_read_4

        subroutine c_iomanager_read_4_bufferify(self, group, root_file, &
                Lroot_file, preserve_contents, use_scr) &
                bind(C, name="SPIO_IOManager_read_4_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_BOOL, C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
            integer(C_INT), value, intent(IN) :: Lroot_file
            logical(C_BOOL), value, intent(IN) :: preserve_contents
            logical(C_BOOL), value, intent(IN) :: use_scr
        end subroutine c_iomanager_read_4_bufferify

        subroutine c_iomanager_load_external_data(self, group, &
                root_file) &
                bind(C, name="SPIO_IOManager_load_external_data")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
        end subroutine c_iomanager_load_external_data

        subroutine c_iomanager_load_external_data_bufferify(self, group, &
                root_file, Lroot_file) &
                bind(C, name="SPIO_IOManager_load_external_data_bufferify")
            use axom_sidre, only : SHROUD_group_capsule
            use iso_c_binding, only : C_CHAR, C_INT
            import :: SHROUD_iomanager_capsule
            implicit none
            type(SHROUD_iomanager_capsule), intent(IN) :: self
            type(SHROUD_group_capsule), intent(IN) :: group
            character(kind=C_CHAR), intent(IN) :: root_file(*)
            integer(C_INT), value, intent(IN) :: Lroot_file
        end subroutine c_iomanager_load_external_data_bufferify

        ! splicer begin class.IOManager.additional_interfaces
        ! splicer end class.IOManager.additional_interfaces

        ! splicer begin additional_interfaces
        ! splicer end additional_interfaces
    end interface

    interface iomanager_new
        module procedure iomanager_new_0
        module procedure iomanager_new_1
    end interface iomanager_new

contains

    function iomanager_new_0(com) &
            result(SHT_rv)
        use iso_c_binding, only : C_PTR
        integer, value, intent(IN) :: com
        type(iomanager) :: SHT_rv
        ! splicer begin class.IOManager.method.new_0
        type(C_PTR) :: SHT_prv
        SHT_prv = c_iomanager_new_0(com, SHT_rv%cxxmem)
        ! splicer end class.IOManager.method.new_0
    end function iomanager_new_0

    function iomanager_new_1(com, use_scr) &
            result(SHT_rv)
        use iso_c_binding, only : C_BOOL, C_PTR
        integer, value, intent(IN) :: com
        logical, value, intent(IN) :: use_scr
        type(iomanager) :: SHT_rv
        ! splicer begin class.IOManager.method.new_1
        logical(C_BOOL) SH_use_scr
        type(C_PTR) :: SHT_prv
        SH_use_scr = use_scr  ! coerce to C_BOOL
        SHT_prv = c_iomanager_new_1(com, SH_use_scr, SHT_rv%cxxmem)
        ! splicer end class.IOManager.method.new_1
    end function iomanager_new_1

    subroutine iomanager_delete(obj)
        class(iomanager) :: obj
        ! splicer begin class.IOManager.method.delete
        call c_iomanager_delete(obj%cxxmem)
        ! splicer end class.IOManager.method.delete
    end subroutine iomanager_delete

    subroutine iomanager_write_0(obj, group, num_files, file_string, &
            protocol)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        integer(C_INT), value, intent(IN) :: num_files
        character(len=*), intent(IN) :: file_string
        character(len=*), intent(IN) :: protocol
        ! splicer begin class.IOManager.method.write_0
        call c_iomanager_write_0_bufferify(obj%cxxmem, group%cxxmem, &
            num_files, file_string, len_trim(file_string, kind=C_INT), &
            protocol, len_trim(protocol, kind=C_INT))
        ! splicer end class.IOManager.method.write_0
    end subroutine iomanager_write_0

    subroutine iomanager_write_1(obj, group, num_files, file_string, &
            protocol, pattern)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        integer(C_INT), value, intent(IN) :: num_files
        character(len=*), intent(IN) :: file_string
        character(len=*), intent(IN) :: protocol
        character(len=*), intent(IN) :: pattern
        ! splicer begin class.IOManager.method.write_1
        call c_iomanager_write_1_bufferify(obj%cxxmem, group%cxxmem, &
            num_files, file_string, len_trim(file_string, kind=C_INT), &
            protocol, len_trim(protocol, kind=C_INT), pattern, &
            len_trim(pattern, kind=C_INT))
        ! splicer end class.IOManager.method.write_1
    end subroutine iomanager_write_1

    subroutine iomanager_write_group_to_root_file(obj, group, file_name)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: file_name
        ! splicer begin class.IOManager.method.write_group_to_root_file
        call c_iomanager_write_group_to_root_file_bufferify(obj%cxxmem, &
            group%cxxmem, file_name, len_trim(file_name, kind=C_INT))
        ! splicer end class.IOManager.method.write_group_to_root_file
    end subroutine iomanager_write_group_to_root_file

    subroutine iomanager_write_blueprint_index_to_root_file(obj, &
            datastore, domain_path, file_name, mesh_path)
        use axom_sidre, only : SidreDataStore
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreDataStore), intent(IN) :: datastore
        character(len=*), intent(IN) :: domain_path
        character(len=*), intent(IN) :: file_name
        character(len=*), intent(IN) :: mesh_path
        ! splicer begin class.IOManager.method.write_blueprint_index_to_root_file
        call c_iomanager_write_blueprint_index_to_root_file_bufferify(obj%cxxmem, &
            datastore%cxxmem, domain_path, &
            len_trim(domain_path, kind=C_INT), file_name, &
            len_trim(file_name, kind=C_INT), mesh_path, &
            len_trim(mesh_path, kind=C_INT))
        ! splicer end class.IOManager.method.write_blueprint_index_to_root_file
    end subroutine iomanager_write_blueprint_index_to_root_file

    subroutine iomanager_read_0(obj, group, file_string, protocol)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: file_string
        character(len=*), intent(IN) :: protocol
        ! splicer begin class.IOManager.method.read_0
        call c_iomanager_read_0_bufferify(obj%cxxmem, group%cxxmem, &
            file_string, len_trim(file_string, kind=C_INT), protocol, &
            len_trim(protocol, kind=C_INT))
        ! splicer end class.IOManager.method.read_0
    end subroutine iomanager_read_0

    subroutine iomanager_read_1(obj, group, file_string, protocol, &
            preserve_contents)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_BOOL, C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: file_string
        character(len=*), intent(IN) :: protocol
        logical, value, intent(IN) :: preserve_contents
        ! splicer begin class.IOManager.method.read_1
        logical(C_BOOL) SH_preserve_contents
        SH_preserve_contents = preserve_contents  ! coerce to C_BOOL
        call c_iomanager_read_1_bufferify(obj%cxxmem, group%cxxmem, &
            file_string, len_trim(file_string, kind=C_INT), protocol, &
            len_trim(protocol, kind=C_INT), SH_preserve_contents)
        ! splicer end class.IOManager.method.read_1
    end subroutine iomanager_read_1

    subroutine iomanager_read_2(obj, group, root_file)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: root_file
        ! splicer begin class.IOManager.method.read_2
        call c_iomanager_read_2_bufferify(obj%cxxmem, group%cxxmem, &
            root_file, len_trim(root_file, kind=C_INT))
        ! splicer end class.IOManager.method.read_2
    end subroutine iomanager_read_2

    subroutine iomanager_read_3(obj, group, root_file, &
            preserve_contents)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_BOOL, C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: root_file
        logical, value, intent(IN) :: preserve_contents
        ! splicer begin class.IOManager.method.read_3
        logical(C_BOOL) SH_preserve_contents
        SH_preserve_contents = preserve_contents  ! coerce to C_BOOL
        call c_iomanager_read_3_bufferify(obj%cxxmem, group%cxxmem, &
            root_file, len_trim(root_file, kind=C_INT), &
            SH_preserve_contents)
        ! splicer end class.IOManager.method.read_3
    end subroutine iomanager_read_3

    subroutine iomanager_read_4(obj, group, root_file, &
            preserve_contents, use_scr)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_BOOL, C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: root_file
        logical, value, intent(IN) :: preserve_contents
        logical, value, intent(IN) :: use_scr
        ! splicer begin class.IOManager.method.read_4
        logical(C_BOOL) SH_preserve_contents
        logical(C_BOOL) SH_use_scr
        SH_preserve_contents = preserve_contents  ! coerce to C_BOOL
        SH_use_scr = use_scr  ! coerce to C_BOOL
        call c_iomanager_read_4_bufferify(obj%cxxmem, group%cxxmem, &
            root_file, len_trim(root_file, kind=C_INT), &
            SH_preserve_contents, SH_use_scr)
        ! splicer end class.IOManager.method.read_4
    end subroutine iomanager_read_4

    subroutine iomanager_load_external_data(obj, group, root_file)
        use axom_sidre, only : SidreGroup
        use iso_c_binding, only : C_INT
        class(iomanager) :: obj
        type(SidreGroup), intent(IN) :: group
        character(len=*), intent(IN) :: root_file
        ! splicer begin class.IOManager.method.load_external_data
        call c_iomanager_load_external_data_bufferify(obj%cxxmem, &
            group%cxxmem, root_file, len_trim(root_file, kind=C_INT))
        ! splicer end class.IOManager.method.load_external_data
    end subroutine iomanager_load_external_data

    ! Return pointer to C++ memory.
    function iomanager_get_instance(obj) result (cxxptr)
        use iso_c_binding, only: C_PTR
        class(iomanager), intent(IN) :: obj
        type(C_PTR) :: cxxptr
        cxxptr = obj%cxxmem%addr
    end function iomanager_get_instance

    subroutine iomanager_set_instance(obj, cxxmem)
        use iso_c_binding, only: C_PTR
        class(iomanager), intent(INOUT) :: obj
        type(C_PTR), intent(IN) :: cxxmem
        obj%cxxmem%addr = cxxmem
        obj%cxxmem%idtor = 0
    end subroutine iomanager_set_instance

    function iomanager_associated(obj) result (rv)
        use iso_c_binding, only: c_associated
        class(iomanager), intent(IN) :: obj
        logical rv
        rv = c_associated(obj%cxxmem%addr)
    end function iomanager_associated

    ! splicer begin class.IOManager.additional_functions
    ! splicer end class.IOManager.additional_functions

    ! splicer begin additional_functions
    ! splicer end additional_functions

    function iomanager_eq(a,b) result (rv)
        use iso_c_binding, only: c_associated
        type(iomanager), intent(IN) ::a,b
        logical :: rv
        if (c_associated(a%cxxmem%addr, b%cxxmem%addr)) then
            rv = .true.
        else
            rv = .false.
        endif
    end function iomanager_eq

    function iomanager_ne(a,b) result (rv)
        use iso_c_binding, only: c_associated
        type(iomanager), intent(IN) ::a,b
        logical :: rv
        if (.not. c_associated(a%cxxmem%addr, b%cxxmem%addr)) then
            rv = .true.
        else
            rv = .false.
        endif
    end function iomanager_ne

end module axom_spio
