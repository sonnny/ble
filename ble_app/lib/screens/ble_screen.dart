import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:universal_ble/universal_ble.dart';
import 'dart:async';
import 'dart:io';
import 'dart:convert';
import './widgets/services_list_widget.dart';

class BleScreen extends StatefulWidget{
  final String deviceId;
  final String deviceName;
  BleScreen(this.deviceId, this.deviceName, {Key? key}) : super(key: key);
  @override State createState() => BleScreenState();}
  
class BleScreenState extends State<BleScreen>{
  bool isConnected = false;
  List<BleService> discoveredServices = [];
  TextEditingController controller = TextEditingController();
  
  ({
    BleService service,
    BleCharacteristic characteristic
  })? selectedCharacteristic;
  
  Future<void> discoverServices() async{
    try{
      var services = await UniversalBle.discoverServices(widget.deviceId);
      discoveredServices.clear();
      setState((){
        discoveredServices = services;});
    } catch (e){print(e);}}
  
  @override void initState(){
    super.initState();
    UniversalBle.onConnectionChange = handleConnectionChange;}
    
  @override void dispose(){
    super.dispose();
    if (isConnected) UniversalBle.disconnect(widget.deviceId);}
    
  void handleConnectionChange(
    String deviceId,
    bool isConnected,
    String? error){
    
    setState((){
      if (deviceId == widget.deviceId){
        this.isConnected = isConnected;}});
        
    if (this.isConnected){
      discoverServices();}}
      
  Future<void> ble_write(val) async {
    Uint8List data = utf8.encode(val);
    try {
      await UniversalBle.writeValue(
        widget.deviceId,
        selectedCharacteristic!.service.uuid,
        selectedCharacteristic!.characteristic.uuid,
        data,
        BleOutputProperty.withResponse);
    } catch (e) {
      print(e);
    }}
        
@override Widget build(BuildContext context){
  return Scaffold(
    backgroundColor: const Color(0xffC4DFCB),
    appBar: AppBar(
        title: Text('${widget.deviceName}-${widget.deviceId}',
          style: TextStyle(fontSize: 16, color: Colors.red))),
          
    body: Column(spacing: 15, children: [
      
      SizedBox(height:10),
      
      Row(spacing: 10, children:[
          SizedBox(width:10),
          ElevatedButton(child: Text('connect'),
            onPressed:() async {
              try{
                await UniversalBle.connect(widget.deviceId);
              } catch (e) {print(e);}}),
          ElevatedButton(child: Text('disconnect'),
            onPressed:(){ UniversalBle.disconnect(widget.deviceId);}),
          if (BleCapabilities.supportsRequestMtuApi)
            ElevatedButton(child: Text('mtu'),
            onPressed:() async {
              int mtu = await UniversalBle.requestMtu(
                widget.deviceId, 247);})]),
                            
 if (selectedCharacteristic != null)
     Padding(padding: EdgeInsets.fromLTRB(10,0,10,0), child: TextField(controller: controller,
      decoration: InputDecoration(border: OutlineInputBorder(), labelText: 'enter text to send'),
      inputFormatters: [LengthLimitingTextInputFormatter(80),],
      onSubmitted: (text){ble_write(text);})),

      //if (deviceType != DeviceType.desktop)
      
      Visibility(visible: selectedCharacteristic == null,
                 child:       ServicesListWidget(
                          discoveredServices: discoveredServices,
                          onTap: (BleService service,
                              BleCharacteristic characteristic) {
                            setState(() {
                              selectedCharacteristic = (
                                service: service,
                                characteristic: characteristic
                              );
                            });
                            }))
                                 
]));}}
