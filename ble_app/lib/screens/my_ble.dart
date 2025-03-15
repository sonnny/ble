import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:universal_ble/universal_ble.dart';
import 'dart:async';
import 'dart:io';
import 'dart:convert';

class MyBle extends StatelessWidget{
  MyBle(this.deviceId, this.service, this.characteristic);
  final String deviceId;
  final BleService service;
  final BleCharacteristic characteristic;
  
 TextEditingController controller = TextEditingController();
  
@override Widget build(BuildContext contet){
return Scaffold(appBar: AppBar(title:Text('my ble')),
body: Column(spacing: 15, children:[
  SizedBox(height:20),
 
  Padding(padding: EdgeInsets.fromLTRB(20,0,10,0), child: TextField(controller: controller,
    decoration: InputDecoration(border: OutlineInputBorder(), labelText: 'enter text to send'),
      inputFormatters: [LengthLimitingTextInputFormatter(80),],
      onSubmitted: (text) async {
        var value = utf8.encode(text);
        try {
          await UniversalBle.writeValue(
            deviceId,
            service.uuid,
            characteristic.uuid,
            value,
            BleOutputProperty.withResponse);
        } catch (e){ print(e); }})),
        
  ElevatedButton(child: Text('disconnect and quit'),
    onPressed:() async {
      await UniversalBle.disconnect(deviceId);
      SystemNavigator.pop();}) 
        
]));}}

