# decipher_text
Rant:
In my free time I read old books. archive.org finds an avid fan in me. I hate the fact I can not copy paste. And I am unable to chooose, what I hate more, nuclear weapons or reading from the raw scan. While I can not destroy the nukes, here we are with a modern GUI front-end for the TesseractOCR.
Sure, there exist quite a few GUI frontends for the TesseractOCR- but none of them good feel enough. Proof-reading in most of them is as far away from optimum as the two poles of a magnet. Most of them feel second class citizen compared to the Commercial OCR programs.
I do not use Windows for anything other than gaming, and even if I did, I often work with multi-lingual texts containing both Latin and Devangari Script which no major commercial OCR software supports.

Dependencies:
1. Qt 5.x
2. Boost
3. libtesseract
4. Imagemagick

Defining features (which would seperate it from other similar FOSS):
1. Better proof-reading. Text the cursor is on should be highlighted in the image.
2. Easy to manage loading and saving of the project files.
3. Efficient handling of memory.
4. Multi-language recognization support
5. Truly cross platforms with binary packages for Linux, FreeBSD, Windows and OS X. Possibly HaikuOS.

#How to Build
qmake
make

Generated binary file is in bin sub-directory.