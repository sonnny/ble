import 'package:flutter/material.dart';

class Help extends StatelessWidget {
  const Help({Key? key}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    return Container(
      color: const Color(0xffC4DFCB),
      child: Column(spacing: 15, children: [
      
Padding(padding: EdgeInsets.fromLTRB(15, 15, 15, 0), child: Text(
"This is a flutter bluetooth demo using universal_ble plugin and has been tested on Google pixel 7a, Samsung Galaxy S10, Linux lite desktop, and Linux lite laptop\n\n On pixel and galaxy android, goto settings->app->give location permission, if you are having problem connecting, try stop restart bluetooh on the laptop and android devices or turn on/off the picow ble devices you are trying to connect",
style: TextStyle(color: Colors.green[900],
  fontWeight: FontWeight.w500))),
  
Padding(padding: EdgeInsets.fromLTRB(15, 0, 15, 0), child: Text(
"for bluetooth permission on android look at the file project_folder/android/app/src/main/AndroidManifest.xml",
style: TextStyle(color: Colors.green[900],
  fontWeight: FontWeight.w500))),
  
Padding(padding: EdgeInsets.fromLTRB(15, 0, 15, 0), child: Text(
"I used a bluetooth dongle CSR 4.0 on the linux desktop and the linux Acer laptop has built in bluetooth,\n\nwhen you press connect, give the app a few seconds to make it work, or press connect few times",
style: TextStyle(color: Colors.green[900],
  fontWeight: FontWeight.w500))), 
        
        ]));}}
