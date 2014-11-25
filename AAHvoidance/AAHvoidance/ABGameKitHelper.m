//
//  ABGameKitHelper.m
//  Pastry Panic
//
//  Created by Alexander Blunck on 27.02.12.
//  Copyright (c) 2012 Ablfx. All rights reserved.
//

#import "ABGameKitHelper.h"
//#import "AppDelegate.h"
//#import "NSData+AES256.h"

//#define APPNAME @"MyAppName"
//#define AESKEY @"RandomKeyHere"

@implementation ABGameKitHelper

@synthesize isAuthenticated, isActivated;


+(void) authenticatePlayer {
    GKLocalPlayer *player = [GKLocalPlayer localPlayer];
    [player authenticateWithCompletionHandler:^(NSError *error) {
        if (player.isAuthenticated) {
            //isAuthenticated = YES;
            NSLog(@"GK - Player successfully authenticated");
            //Report possible cached Achievements / Scores
            //[self reportCachedAchievements];
            //[self reportCachedScores];
        }
        
        if (error != nil) {
            NSLog(@"GK - Error in authenticatePlayer - Error: %@", error);
        }
    }];
}



@end
