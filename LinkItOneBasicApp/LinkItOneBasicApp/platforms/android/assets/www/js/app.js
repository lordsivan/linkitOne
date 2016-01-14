// Ionic Starter App

// angular.module is a global place for creating, registering and retrieving Angular modules
// 'starter' is the name of this angular module example (also set in a <body> attribute in index.html)
// the 2nd parameter is an array of 'requires'
// 'starter.services' is found in services.js
// 'starter.controllers' is found in controllers.js
angular.module('starter', ['ionic', 'starter.controllers',
                            'starter.services',
                            'bleServiceModule',
                            'ServiceInitModule',
                            'settingsModule',
                            'configureIOTModule',
                            'terminalModule',
                            'wifiModule',
                            'dashboardModule',
                            'homeModule'])

.run(function($ionicPlatform) {
  $ionicPlatform.ready(function() {
    // Hide the accessory bar by default (remove this to show the accessory bar above the keyboard
    // for form inputs)
    if (window.cordova && window.cordova.plugins && window.cordova.plugins.Keyboard) {
      cordova.plugins.Keyboard.hideKeyboardAccessoryBar(true);
    }
    if (window.StatusBar) {
      // org.apache.cordova.statusbar required
      StatusBar.styleLightContent();
    }
  });
})
.controller('AppController', function($scope, $ionicSideMenuDelegate,$LStore,bleService) {
  $scope.toggleLeft = function() {
    $ionicSideMenuDelegate.toggleLeft();
  };
  $scope.refreshBLE = function(){
    $scope.settingsModel = {
        "selectedBLE":"",
        "blueToothList":[]
    };
    $scope.settingsModel= $LStore.getObject("settingsModel",$scope.settingsModel);
        // if(typeof $scope.settingsModel.selectedBLE.name != 'undefined'){
        //    $scope.configuredBLE= true;
        // }
         //console.log("saved selected BLE"+$scope.settingsModel.selectedBLE.name);
         //console.log("saved selected BLE"+$scope.settingsModel.selectedBLE.address);
         //console.log("saved selected BLE"+$scope.configuredBLE);
         //$scope.$apply();
         //});
console.log("---------------------------------------------");
bleService.deviceConnect($scope.settingsModel.selectedBLE.address).then(
        function(list){
            console.log("connected successfully");
        },
        function(){
            console.log("error");
        }
    );
};



})
.config(function($stateProvider, $urlRouterProvider, $ionicConfigProvider) {

$ionicConfigProvider.navBar.alignTitle('center')
})
.config(function($stateProvider, $urlRouterProvider) {

  // Ionic uses AngularUI Router which uses the concept of states
  // Learn more here: https://github.com/angular-ui/ui-router
  // Set up the various states which the app can be in.
  // Each state's controller can be found in controllers.js
  $stateProvider

  // setup an abstract state for the tabs directive
    .state('tab', {
    url: "/tab",
    abstract: true,
    templateUrl: "templates/menu.html"
  })
  .state('tab.Ble', {
      url: '/Ble',
      views: {
          'appContent': {
              templateUrl: 'templates/Settings/Settings.html',
              controller: 'settingsController'
          }
      }
  })
    .state('tab.terminal', {
        url: '/terminal',
        views: {
            'appContent': {
                templateUrl: 'templates/Terminal/Terminal.html',
                controller: 'terminalController'
            }
        }
    })
  .state('tab.configureIOT', {
      url: '/configureIOT',
      views: {
          'appContent': {
              templateUrl: 'templates/ConfigureIOT/ConfigureIOT.html',
              controller: 'configureIOTController'
          }
      }
  })
   .state('tab.wifi', {
        url: '/wifi',
        views: {
            'appContent': {
                templateUrl: 'templates/ConfigureIOT/wifi/wifi.html',
                controller: 'wifiController'
            }
        }
    })
  .state('tab.home', {
        url: '/home',
        views: {
            'appContent': {
                templateUrl: 'templates/home.html',
                controller: 'homeController'
            }
        }
    })
    .state('tab.dashboard', {
            url: '/dashboard',
            views: {
                'appContent': {
                    templateUrl: 'templates/Dashboard/Dashboard.html',
                    controller: 'dashboardController'
                }
            }
        })
    ;

  // if none of the above states are matched, use this as the fallback
  $urlRouterProvider.otherwise('/tab/home');

});
