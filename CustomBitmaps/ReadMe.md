
Here's how to create a custom Bitmap for your MakeItHackin Badge.  This requires you to reprogram your badge, so you'll need an AVR programmer and a way to upload the code (Arduino IDE can do it)

I briefly cover this process in the YouTube tutorial: https://youtu.be/G82_usjS0wA

Create a bitmap that is 128x32 pixels.  You can use the photoshop template in this folder, or rework one of the bitmaps included.  When I save the template as a bitmap in photoshop I use the following settings for bitmap: Windows / 24 bit.

Next, convert bitmap to code: https://javl.github.io/image2cpp/
Use the following settings:
Background color: black
Invert image colors: yes
Canvas size: 128x32
Code output format: Arduino
Draw mode: Vertical - 1 bit per pixel

Then copy the output code and paste it into the variable  "customBitmap", which looks like a big array of HEX.  It'll be the last one of these you see in the code.  Make sure to replace the previous code inside that variable.

Finally, change the variable "badgeType" to the value of 8.  This will tell the code to display the customBitmap screen.

That's it!

Enjoy!
  
