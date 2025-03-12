# ble
project for flutter android app ble and picow ble

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
  
  
  
