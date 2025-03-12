
import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import 'package:universal_ble/universal_ble.dart';
import './widgets/scanned_item_widget.dart';
import './ble_screen.dart';
import '../global.dart'; // some styling constant

class BleScan extends StatefulWidget{
  BleScan({Key? key}) : super(key: key);
  @override State createState() => BleScanState();}
  
class BleScanState extends State<BleScan>{

  final bleDevices = <BleDevice>[];
  bool isScanning = false;
  QueueType queueType = QueueType.global;
  TextEditingController controller = TextEditingController();
 
  void showSnackbar(message){
    ScaffoldMessenger.of(context).showSnackBar(
      SnackBar(content: Text(message.toString())),);}
  
  @override void initState(){
    super.initState();
    UniversalBle.queueType = queueType;
    UniversalBle.timeout = const Duration(seconds: 10);
    UniversalBle.onScanResult = (result){
      int index = bleDevices.indexWhere((e) => e.deviceId == result.deviceId);
      if (index == -1){
        bleDevices.add(result);
      } else {
        if (result.name == null && bleDevices[index].name != null){
          result.name = bleDevices[index].name;
        }
        bleDevices[index] = result;
      }
      setState(() {});
    };}
  
  Future<void> startScan() async{
    await UniversalBle.startScan(
      scanFilter: ScanFilter(
        withServices: [],
        withManufacturerData: [],
        withNamePrefix: [controller.text]));}
  
  Future<void> getSystemDevices() async{
    List<BleDevice> myDevices = await UniversalBle.getSystemDevices();
    if (myDevices.isEmpty){
      showSnackbar("No system connected devices found");}
    setState(() {
      bleDevices.clear();
      bleDevices.addAll(myDevices);});}
      
@override Widget build(BuildContext context){
  return Container(child: Column(spacing: 15, children:[
 
     Padding(padding: EdgeInsets.fromLTRB(20,15,20,0), child: TextField(controller: controller,
      decoration: InputDecoration(border: OutlineInputBorder(), labelText: 'enter device name prefix:'))),
          
    Row(spacing: 5, children:[
      SizedBox(width: 5),
      ElevatedButton(child: Text('start scan'),
            onPressed:() async{
              setState(() {
                bleDevices.clear();
                isScanning = true;});
                try{
                  await startScan();
                } catch (e) {
                  setState(() {
                    isScanning = false;});
                  showSnackbar(e);}}),
     ElevatedButton(child: Text('stop scan'),
            onPressed:() async {
              await UniversalBle.stopScan();
              setState(() {
                isScanning = false;});}),
     ElevatedButton(child: Text('Sys devices'),
             onPressed: getSystemDevices,)]),
    
    Expanded(child: isScanning && bleDevices.isEmpty
      ? Center(child: CircularProgressIndicator.adaptive())
      : !isScanning && bleDevices.isEmpty
        ? Text('scan for devices',style: myStyle)
        : ListView.separated(
          itemCount: bleDevices.length,
          separatorBuilder: (context, index) => const Divider(),
          itemBuilder: (context, index){
            BleDevice device = bleDevices[bleDevices.length - index - 1];
            return ScannedItemWidget(
              bleDevice: device,
              onTap:(){
                Navigator.push(
                  context,
                  MaterialPageRoute(
                    builder: (context) => BleScreen(
                      device.deviceId,
                      device.name ?? "unknown")));
              UniversalBle.stopScan();
              setState(() {
                isScanning = false;});});}))]));}}       
