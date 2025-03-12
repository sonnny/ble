
//https://www.geeksforgeeks.org/flutter-custom-bottom-navigation-bar/
//problem running debug task
//flutter error: execution failed for task app:compileDebugJavaWithJavac
//solution: https://stackoverflow.com/questions/59177152/flutter-error-execution-failed-for-task-appcompiledebugjavawithjavac

//filename: android/settings.gradle
//before: id "com.android.application" version "8.1.0" apply false
//after: id "com.android.application" version "8.3.2" apply false

//filename: android/gradle/wrapper/gradle-wrapper.properties
//before: distributionUrl=https://services.gradle.org/distributions/gradle-8.3-all.zip
//after: distributionUrl=https://services.gradle.org/distributions/gradle-8.4-all.zip

// I used window_manager plugin to set screen size to 400, 900 (my android pixel size screen
// so when I debug on linux desktop, the screen looks the same on pixel and I don't have
// to keep resizing the screen, I can see overflow right away on the desktop

// during development I used picow projects/picow/ble_cli
// during development I used flutter projects/flutter/bottom_nav


import 'package:flutter/material.dart';
import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';
import 'package:window_manager/window_manager.dart';
import './screens/ble_scan.dart';
import './screens/page4.dart';
import './screens/home.dart';
import './screens/help.dart';


TextStyle myStyle = TextStyle(color: Colors.green[900],
  fontWeight: FontWeight.w500);

void main() {  //use on mobile 

/*
comment for desktop starts
void main() async {

  WidgetsFlutterBinding.ensureInitialized();
  await windowManager.ensureInitialized();
  WindowOptions windowOptions = WindowOptions(
    size: Size(400, 900),
    center: true,
    backgroundColor: Colors.transparent,
    skipTaskbar: false,
    titleBarStyle: TitleBarStyle.hidden);
    
  windowManager.waitUntilReadyToShow(windowOptions, () async {
    await windowManager.show();
    await windowManager.focus();});
  
comment for desktop end  
*/
    
  runApp(MyApp());}

class MyApp extends StatelessWidget {
  MyApp({Key? key}) : super(key: key);

  // This widget is the root of your application.
  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Bottom NavBar Demo',
      theme: ThemeData(
        primaryColor: const Color(0xff2F8D46),
        splashColor: Colors.transparent,
        highlightColor: Colors.transparent,
        hoverColor: Colors.transparent,
      ),
      debugShowCheckedModeBanner: false,
      home: const HomePage(),
    );
  }
}

class HomePage extends StatefulWidget {
  const HomePage({Key? key}) : super(key: key);

  @override
  _HomePageState createState() => _HomePageState();
}

class _HomePageState extends State<HomePage> {
  int pageIndex = 0;

  final pages = [
    Home(),
    BleScan(),
    Help(),
    Page4(),
  ];

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      backgroundColor: const Color(0xffC4DFCB),
      appBar: AppBar(
        leading: Icon(
          Icons.menu,
          color: Theme.of(context).primaryColor,
        ),
        title: Text(
          "bluetooth demo",
          style: TextStyle(
            color: Theme.of(context).primaryColor,
            fontSize: 25,
            fontWeight: FontWeight.w600,
          ),
        ),
        centerTitle: true,
        backgroundColor: Colors.white,
        
        actions: [
          IconButton(icon: Icon(Icons.exit_to_app),
          onPressed:() => SystemNavigator.pop())
        ]
      ),
      body: pages[pageIndex],
      bottomNavigationBar: buildMyNavBar(context),
    );
  }

  Container buildMyNavBar(BuildContext context) {
    return Container(
      height: 60,
      decoration: BoxDecoration(
        color: Theme.of(context).primaryColor,
        borderRadius: const BorderRadius.only(
          topLeft: Radius.circular(20),
          topRight: Radius.circular(20),
        ),
      ),
      child: Row(
        mainAxisAlignment: MainAxisAlignment.spaceAround,
        children: [
          IconButton(
            enableFeedback: false,
            onPressed: () {
              setState(() {
                pageIndex = 0;
              });
            },
            icon: pageIndex == 0
                ? const Icon(
                    Icons.home_filled,
                    color: Colors.white,
                    size: 35,
                  )
                : const Icon(
                    Icons.home_outlined,
                    color: Colors.white,
                    size: 35,
                  ),
          ),
          IconButton(
            enableFeedback: false,
            onPressed: () {
              setState(() {
                pageIndex = 1;
              });
            },
            icon: pageIndex == 1
                ? const Icon(
                    Icons.bluetooth_searching_outlined,
                    color: Colors.white,
                    size: 35,
                  )
                : const Icon(
                    Icons.bluetooth,
                    color: Colors.white,
                    size: 35,
                  ),
          ),
          IconButton(
            enableFeedback: false,
            onPressed: () {
              setState(() {
                pageIndex = 2;
              });
            },
            icon: pageIndex == 2
                ? const Icon(
                    Icons.help_outlined,
                    color: Colors.white,
                    size: 35,
                  )
                : const Icon(
                    Icons.help_outline,
                    color: Colors.white,
                    size: 35,
                  ),
          ),
          IconButton(
            enableFeedback: false,
            onPressed: () {
              setState(() {
                pageIndex = 3;
              });
            },
            icon: pageIndex == 3
                ? const Icon(
                    Icons.exit_to_app,
                    color: Colors.white,
                    size: 35,
                  )
                : const Icon(
                    Icons.exit_to_app,
                    color: Colors.white,
                    size: 35,
                  ),
          ),
        ],
      ),
    );
  }
}
