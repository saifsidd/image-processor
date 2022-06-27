// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  img->width = width;
  img->height = height;
  

  Matrix_init(&img->red_channel, width, height);
  Matrix_init(&img->green_channel, width, height);
  Matrix_init(&img->blue_channel, width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  char junk[2];
  int width, height, r, g, b, row, col, intJunk;
  is >> junk[0] >> junk[1] >> width >> height >> intJunk;
  
  Image_init(img, width, height);

  row = 0;
  col = 0;

  while (is || (col == width && row == height)) {
    is >> r >> g >> b;
    Image_set_pixel(img, row, col, {r, g, b});
    ++col;
    if (col == width) {
      row++;
      col = 0;
    }
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3" << std::endl;
  os << img->width << " " << img->height << std::endl;
  os << "255" << std::endl;
  for (int row = 0; row < img->height; row++) {
    for (int col = 0; col < img->width; col++) {
      os << *(Matrix_at(&img->red_channel, row, col)) << " ";
      os << *(Matrix_at(&img->green_channel, row, col)) << " ";
      os << *(Matrix_at(&img->blue_channel, row, col)) << " ";
    }
    os << std::endl;
  }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  Pixel *pix = new Pixel; 
  pix->r = *(Matrix_at(&img->red_channel, row, column));
  pix->g = *(Matrix_at(&img->green_channel, row, column));
  pix->b = *(Matrix_at(&img->blue_channel, row, column));
  return *pix;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
    *(Matrix_at(&(img->red_channel), row, column)) = color.r;
    *(Matrix_at(&(img->green_channel), row, column)) = color.g;
    *(Matrix_at(&(img->blue_channel), row, column)) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  Matrix_fill(&(img->red_channel), color.r);
  Matrix_fill(&(img->green_channel), color.g);
  Matrix_fill(&(img->blue_channel), color.b);
  // for (int row = 0; row < img->height; row++) {
  //   for (int col = 0; col < img->width; col++) {
  //     *(Matrix_at(&(img->red_channel), row, col)) = color.r;
  //     *(Matrix_at(&(img->green_channel), row, col)) = color.g;
  //     *(Matrix_at(&(img->blue_channel), row, col)) = color.b;
  //   }
  // }
}
