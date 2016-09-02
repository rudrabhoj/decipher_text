# Decipher Text
![Screenshot](http://i.imgur.com/hdMn0tf.png "Build from August 12, 2016")

##Rant
In my free time I read old books. archive.org finds an avid fan in me. I hate the fact I cannot copy paste. I am unable to decide what I hate more, nuclear weapons or reading from the raw scan of antiquated books. While I can't make the nukes disappear, here we are with a modern GUI front-end for TesseractOCR.  
Sure, there exist quite a few GUI frontends for the TesseractOCR- but none of them feel good enough. Proof-reading in most of them is as far away from optimum as the two poles of a magnet. Most of them feel second class citizen compared to the Commercial OCR programs.  
I do not use Windows for anything other than gaming, and even if I did, I often work with multi-lingual texts containing both Latin and Devangari writing systems which no major commercial OCR software supports.  

##Dependencies
1. Qt 5.x (5.7+ recommended)   
2. libtesseract  
3. Leptonica  
4. Imagemagick  

##Defining features (which would seperate it from similar FOSS)
1. Better proof-reading. Text the cursor is on will be highlighted in the image.  
2. Easy to manage loading and saving of the project files.  
3. Efficient handling of memory.  
4. Recognition support for the multi-lingual text.  
5. Multi-core support  
6. Built-in image manipulation support to make OCR process simpler  
7. Truly cross platform with binary packages for Linux, FreeBSD, Windows and OS X. Possibly even HaikuOS.  

##How to Build
qmake  
make
###Note for Windows Users
I recently upgraded to Windows 10 and ironically has been not too annoyed. So I get to test compiling there.
Your best bet would be to use MSYS2. Get leptonica from there and follow the instructions given by the Tesseract Project github to learn how to compile tesseract properly with MSYS2.
There are lot of guides on the internet on how to setup Qt 5 with MYSYS2. Follow them.
I recommend [this](http://wiki.netbeans.org/HowToSetup64-BitQt5WithNetBeans8.0OnWindows) tutorial.
You can ignore the netbeans part ;)
Once you have everything up and running, just do what the linux/freebsd folks are expected to do:
qmake
make

And you should be done.
One more thing. Once you compile, convert.exe should be accessible from bin/imagemagick/convert.exe on windows.
Undecided as of yet if it should be integrated to settings to select the path.
Reason being I do not find it reasonable for windows users to know what the heck is imagemagick and find path to it.
Person making windows package should be made to keep it there.

Generated binary file is in bin sub-directory.
