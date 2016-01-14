 var app = angular.module('ServiceInitModule', ['ionic', 'ionic.utils' ]);

    app.controller
        ('ServiceInitCtrl',
            ['$scope','$rootScope','$window','$LStore','bleService',
                function($scope,$rootScope,$window,$LStore,bleService) {
                }
            ]
         );