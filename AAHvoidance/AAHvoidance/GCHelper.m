//
//  GCHelper.m
//  AAHvoidance
//
//  Created by Johnny Murphy on 31/12/2012.
//
//

#import "GCHelper.h"
#import <RevMobAds/RevMobAds.h>

@implementation GCHelper


@synthesize gameCenterAvailable;

#pragma mark Initialization

static GCHelper *sharedHelper = nil;
+ (GCHelper *) sharedInstance {
    if (!sharedHelper) {
        sharedHelper = [[GCHelper alloc] init];
    }
    return sharedHelper;
}


- (BOOL)isGameCenterAvailable {
    // check for presence of GKLocalPlayer API
    Class gcClass = (NSClassFromString(@"GKLocalPlayer"));
    
    // check if the device is running iOS 4.1 or later
    NSString *reqSysVer = @"4.1";
    NSString *currSysVer = [[UIDevice currentDevice] systemVersion];
    BOOL osVersionSupported = ([currSysVer compare:reqSysVer
                                           options:NSNumericSearch] != NSOrderedAscending);
    
    return (gcClass && osVersionSupported);
}


- (id)init {
    if ((self = [super init])) {
        gameCenterAvailable = [self isGameCenterAvailable];
        if (gameCenterAvailable) {
            NSNotificationCenter *nc =
            [NSNotificationCenter defaultCenter];
            [nc addObserver:self
                   selector:@selector(authenticationChanged)
                       name:GKPlayerAuthenticationDidChangeNotificationName
                     object:nil];
        }
    }
    return self;
}

- (void)authenticationChanged {
    
    if ([GKLocalPlayer localPlayer].isAuthenticated && !userAuthenticated) {
        NSLog(@"Authentication changed: player authenticated.");
        userAuthenticated = TRUE;
    } else if (![GKLocalPlayer localPlayer].isAuthenticated && userAuthenticated) {
        NSLog(@"Authentication changed: player not authenticated");
        userAuthenticated = FALSE;
    }
    
}

#pragma mark User functions

- (void)authenticateLocalUser {
    
    if (!gameCenterAvailable) return;
    
    NSLog(@"Authenticating local user...");
    if ([GKLocalPlayer localPlayer].authenticated == NO) {
        [[GKLocalPlayer localPlayer] authenticateWithCompletionHandler:nil];
    } else {
        NSLog(@"Already authenticated!");
    }
}

-(void) showLeaderboard:(NSString*)leaderboardID {
    
    if(userAuthenticated)
    {
        
        GKLeaderboardViewController *leaderboardViewController = [[GKLeaderboardViewController alloc] init];
        leaderboardViewController.leaderboardDelegate = self;
        if (leaderboardID) {
            leaderboardViewController.category = leaderboardID;
        }
        
        UIWindow *keyWindow = [[UIApplication sharedApplication] keyWindow];
        [[keyWindow rootViewController] presentModalViewController:leaderboardViewController animated:YES];
    }
    
    else
    {
        [[GCHelper sharedInstance] authenticateLocalUser];
    }
    

}

- (void)leaderboardViewControllerDidFinish:(GKLeaderboardViewController *)viewController
{
	[viewController dismissModalViewControllerAnimated:YES];
	[viewController release];
}


-(void) reportScore:(int)score forLeaderboard:(NSString*)leaderboardName {
    GKScore *scoreReporter = [[[GKScore alloc] initWithCategory:leaderboardName] autorelease];
    scoreReporter.value = score;
    
    [scoreReporter reportScoreWithCompletionHandler:^(NSError *error) {
        if (error != nil){
            NSLog(@"GK - Error during reportScore: - Error: %@", error);
            [self cacheScore:scoreReporter];
        } else {
            NSLog(@"GK - Score:%i Leaderboard:%@ reported", score, leaderboardName);
        }
    }];
}

-(void) addlink{
    
    RevMobAdLink *ad = [[RevMobAds session] adLinkWithPlacementId:@"50e604d604ef690e00000012"]; // you must retain this object
    ad.delegate = self;
    [ad loadAd];
    [ad openLink];
    
    
    //[[RevMobAds session]   openAdLinkWithDelegate:self];
   /*
    RevMobFullscreen *fullscreen = [[RevMobAds session] fullscreenWithPlacementId:@"50e5fb9b92fb330e00000001"];
    [fullscreen showAd];
    */
}





@end
