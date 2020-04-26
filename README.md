== Hercules ROM font compiler

The makerom.c file takes the raw ROM dump from the Hercules Graphics Card then
copies the glyphs to the high and low banks of the output rom image.

This is because we only overlay a selection of glyphs, falling back to the stock
glyphs.

The implemented glyphs are enumerated in the charlist variable.

The program then iterates through the list of possible glyhs, copying them from
the XBM header file, reversing the bit order, then writing out the high and low
glyphs to the combined ROM image.

The XBM file was created in Gimp by generating an image 8 pixels wide by 2048
pixels tall.  I used Filter->Render->Grid to draw a grid on a semi-opque layer
with cells 18 pixels tall and lines 1 pixel wide.  The font was rendered with
the text tool set to 12 pixels tall and full hinting, which made an 18 pixel
tall character box.

I tried using libgd to generate the glyphs with FreeType, but the hinting was
awful and I couldn't find any way to make it better, GIMP simply did a better
job.

I used the grid to manually adjust the placement of the characters in the boxes.

Characters with a drop, like g and j, would get truncated if the bottom of the
drop was on line 14, it seems the display controller did not allow that.

Once the characters were adjusted, I cropped the image to 8x1692 and exported it
as an XBM.  For some reason XBM images are stored right to left instead of left
to right, so the bitmaps need reversing, hence the reverse routine I
appropriated from Stack Overflow.
