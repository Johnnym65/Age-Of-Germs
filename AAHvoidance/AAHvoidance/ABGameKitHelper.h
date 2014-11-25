//
//  ABGameKitHelper.h
//  Pastry Panic
//
//  Created by Alexander Blunck on 27.02.12.
//  Copyright (c) 2012 Ablfx. All rights reserved.
//

//#import <Foundation/Foundation.h>
#import <GameKit/GameKit.h>

@interface ABGameKitHelper : NSObject <GKLeaderboardViewControllerDelegate, GKAchievementViewControllerDelegate>

@property (nonatomic) BOOL isAuthenticated;
@property (nonatomic) BOOL isActivated;


+(void) authenticatePlayer;


@end
