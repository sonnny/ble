# ble
project for flutter android app ble and picow ble

this is my first github from local repository, I finally decided to learn git

  git config user.name "John Doe"
  git config user.mail "john_doe@yahoo.com"

  git status  --  checks for tracking files
  git add filename or directory  -- tracks file or directory
  git commit -m "add your comment here"
  
to upload from my local repository to github.com, get a token:

  got to your github.com account
  make sure the repository exists already
  click on your repository where to push the changes
  on your git profile (upper right hand corner) click on settings
  on the left hand side of the screen, scroll down and click on developers settings
  click on personal access tokens
  click tokens (classic)
  click generate new token
  copy the token locally
  
to push your changes
  on the root folder of your local repository
  git push
  enter your github.com username
  on password cut and paste the token you generated from above
  hit enter
  
  edit .gitignore for files you don't want to upload to github.com
  .gitignore can be files or directory or sub directory

this project is tested on linux desktop, linux laptop, google pixel 7a, samsung galaxy s10+, picow, m5atom-lite, it also uses universal_ble for flutter android app that can run on a linux desktop or android mobile phone without changes

current user functions:

rgb red  --  change ws2812 to red
rgb blue
rgb green

blink 10 200  --  blink picow led 10 times with delay of 200 ms

blink_rgb 10 200  --  blink rgb 10 times delay of 200 ms
                        blink red delay 200 ms
                        blink green delay 200 ms
                        blink blue delay 200 ms
                        repeat this ten tiems

flutter:
  flutter create ble_app --empty
  overwrite lib directory to this lib directory
  on file android/app/src/main/AndroidManifest.xml add bluetooth permissions
    check universal_ble plugin for specifics permission
  add plugins:
    flutter pub add expandable
    flutter pub add universal_ble
    flutter pub window_manager
    
  to test in linux desktop and laptop edit lib/main.dart
  and uncomment the dekstop notes, the reason for this is that when you debug on a
  desktop the windows are wide and height is big compare to a mobile app, so by
  uncommenting dekstop notes, the flutter will run on a desktop with width 400 by height 900
  more like a mobile app, if you don't care about the size then you don't have to worry about
  the dekstop comments
  
  on rp2040 picow follow these steps to generate .uf2 file
  clone this repository
  cd ble/picow/example
  mkdir build
  cd build
  cmake ..
  make
  put picow in reset and copy the resulting .uf2 file
  when compiling for the picow edit the CMakeLists.txt to reflect your own PICO_SDK_PATH
  
  to test the flutter and picow, on your android app, goto settings, goto apps, click ble_app,
  give location permission.
  
  plug in the picow, attach an ws2812 led to gpio13
  on mobile app put pico as filter for manufacturer's name prefix
  if pico shows up on the list, touch the arrow, you will be brought in another screen
  press connect and discovered services will show up, touch the write characteristic
  enter string 'rgb red' press return and the picow ws2812 led should lit up in red
  
  to add your own functions, edit include/user_functions.h, src/user_functions.c,
    src/process.c line 9 (this saves processing time in the loop). See include/ws2812.h and src/ws2812.c for
    example of adding functions, this is from https://github.com/fapplin/rp2040-pico-command-line-interpreter
    
    
  
  
  
