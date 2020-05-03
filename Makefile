FORCE:

compaq.xbm: FORCE
	convert -background white -fill black -font Px437_CompaqThin_8x14.ttf -size 8x1700 -pointsize 15 -density 72 -interline-spacing 4 label:@chars.txt -monochrome $@

text.xbm: FORCE
	convert -background white -fill black -font Comic-Sans-MS -strokewidth 0 -size 8x1700 -gravity North -pointsize 12 -density 72 label:@chars.txt -monochrome $@

makerom: text.xbm
	gcc -o $@ makerom.c
