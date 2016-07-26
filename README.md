# decipher_text
##Rant
In my free time I read old books. archive.org finds an avid fan in me. I hate the fact I cannot copy paste. I am unable to decide what I hate more, nuclear weapons or reading from the raw scan of antiquated books. While I can't make the nukes disappear, here we are with a modern GUI front-end for TesseractOCR.  
Sure, there exist quite a few GUI frontends for the TesseractOCR- but none of them feel good enough. Proof-reading in most of them is as far away from optimum as the two poles of a magnet. Most of them feel second class citizen compared to the Commercial OCR programs.  
I do not use Windows for anything other than gaming, and even if I did, I often work with multi-lingual texts containing both Latin and Devangari writing systems which no major commercial OCR software supports.  

##Dependencies
1. Qt 5.x   
2. libtesseract  
3. Imagemagick  

##Defining features (which would seperate it from other similar FOSS)
1. Better proof-reading. Text the cursor is on should be highlighted in the image.  
2. Easy to manage loading and saving of the project files.  
3. Efficient handling of memory.  
4. Recognition support for the multi-lingual text.  
5. Truly cross platform with binary packages for Linux, FreeBSD, Windows and OS X. Possibly even HaikuOS.  

##How to Build
qmake  
make  

Generated binary file is in bin sub-directory.
