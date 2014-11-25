//PrinceMessage.mm (.mm means its objective-c++?  Which means you can access it in c++?  This file can combine c++ and objective c?)
#include "ObjCCalls.h"
#include "GCHelper.h" 
#import <RevMobAds/RevMobAds.h>
//#import "cocos2dx/platform/ios/EAGLView.h"



void ObjCCalls::AuthenLocalPlayer()
{
    [[GCHelper sharedInstance] authenticateLocalUser];
}

void ObjCCalls::ShowLeaderboard()
{
    NSString *baseString = @"AOGTopPlayers";
    [[GCHelper sharedInstance] showLeaderboard:(baseString)];
}

void ObjCCalls::ReportScore(int score)
{
    NSString *baseString = @"AOGTopPlayers";
    [[GCHelper sharedInstance] reportScore:(score) forLeaderboard:(baseString)];
    
    
}

void ObjCCalls::StartSession()
{    
    [RevMobAds startSessionWithAppID:@"50df5ddc2148e3fc14000001"];
    //[RevMobAds session].testingMode = RevMobAdsTestingModeWithAds;
    
    [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];
    
    // Override point for customization after application launch.
    //self.viewController = [[[SampleAppViewController alloc] init] autorelease];
    //self.window.rootViewController = self.viewController;
    //[makeKeyAndVisible];
    
    //return YES;
}

void ObjCCalls::FullScreenAdd()
{
    RevMobFullscreen *fullscreen = [[RevMobAds session] fullscreenWithPlacementId:@"50e5fb9b92fb330e00000001"];
    [fullscreen showAd];
}

void ObjCCalls::LinkAdd()
{
    [[GCHelper sharedInstance] addlink];
}

