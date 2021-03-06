
Generating figures
==================

Most of the figures that accompany the example code snippets are generated
in this way:

1. Run the primal first example `primal_introduction_ex` in this `figs` 
   directory.  This generates several Asymptote source files with extension
   `.asy`.
2. Compile each source file to PNG format with Asymptote.  For example, run
   `asy -f png showClip.png`.
3. Use ImageMagick `convert` to change the white background of the PNG 
   images to transparent.  For example, run
   `convert showClip.png -transparent white showClip.png`

Asymptote (see http://asymptote.sourceforge.net/) is a vector drawing package.
Despite having its main project page on sourceforge.net, the actual source
repository is on github, where development continues apace.  ImageMagick (see
https://www.imagemagick.org/) is a well-known and widely-installed image
manipulation suite.

The spatial index images are not generated by running `primal_introduction_ex`.
The file `showUniformGrid.asy` was hand-written and should be compiled to
PNG format like the other `.asy` files.  The BVHTree example figures were
generated in the following way:

1. Run `primal_introduction_ex`.  This generates `BVHTree.out.vtk`.
2. Edit `BVHTree.out.vtk` to add the geometry for the triangles used in the 
   BVHTree example (see function `makeBVHTreeTriangles()` in
   `primal_introduction.cpp`).  Save this file as `BVHTree.3.vtk`.
3. Remove the level-three bounding boxes; save this file as `BVHTree.2.vtk`.
4. Remove the level-two bounding boxes; save this file as `BVHTree.1.vtk`.
5. Remove the level-one bounding boxes; save this file as `BVHTree.0.vtk`.
6. Render the `.vtk` files into `.png` files with your "favorite"
   visualization tool (VisIt or Paraview).  Make sure the background is
   rendered as transparent.
