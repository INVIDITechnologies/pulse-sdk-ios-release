//
//  INOmidAdSession.h
//  Pulse
//
//  Created by Nic Henriksson on 2020-06-01.
//  Copyright © 2020 Invidi. All rights reserved.
//
#import <Foundation/Foundation.h>

#import "OOPulseVideoAd.h"
#import "INOmidFriendlyObstruction.h"

/**
Class that enables communication with the Open Measurement SDK for Pulse iOS SDK.
*/
@interface INOmidAdSession : NSObject


/**
  Creates OMID ad session and notifies all verification providers that the ad session has started and ad view tracking will begin.
   **This should be called before playing ad content**, otherwise OM SDK ad session events will not be recorded.
 
  If there are any friendly obstructions that OM SDK should exclude from all viewability calculations, you should use `+[INOmidAdSession createOmidAdSessionWithView:pulseVideoAd:friendlyObstructions:]` method instead.
 
  It is possible to register friendlyObstructions later on as well, when they appear during the ad playback, by using `+[INOmidAdSession addFriendlyObstructions:]  `

  @param adView The native view that OMID should consider for viewability tracking.
  @param ad The `OOPulseVideoAd` that should be displayed.
  @param contentUrl containing the deep link URL for the app screen that is displaying the ad.
 */
+ (void)createOmidAdSessionWithView:(UIView *_Nonnull)adView
                       pulseVideoAd:(id<OOPulseVideoAd>_Nonnull)ad
                         contentUrl:(NSString* _Nullable)contentUrl;

/**
 Creates OMID ad session and notifies all verification providers that the ad session has started and ad view tracking will begin.
  **This should be called before playing ad content**, otherwise OM SDK ad session events will not be recorded.

 If there aren't any friendlyObstructions, you should use `+[INOmidAdSession createOmidAdSessionWithView:pulseVideoAd:]` method instead.

 @param adView The native view that OMID should consider for viewability tracking.
 @param ad The `OOPulseVideoAd` that should be displayed.
 @param contentUrl containing the deep link URL for the app screen that is displaying the ad.
 @param obstructions The friendly obstructions that OMID will exclude from all viewability calculations.
*/
+ (void)createOmidAdSessionWithView:(UIView *_Nonnull)adView
                       pulseVideoAd:(id<OOPulseVideoAd>_Nonnull)ad
                         contentUrl:(NSString* _Nullable)contentUrl
               friendlyObstructions:(NSArray<INOmidFriendlyObstruction *> *_Nullable)obstructions;

/**
 adds friendly obstructions. Use this method to add friendly obstructions that haven't been sent already while creating OMID ad session using `+[INOmidAdSession createOmidAdSessionWithView:pulseVideoAd:friendlyObstructions:]`

 This method will have no affect if called after the omid ad session has finished.
 
 @param obstructions The friendly obstructions to be excluded from all ad session viewability calculations.
*/
+ (void)addFriendlyObstructions:(NSArray<INOmidFriendlyObstruction *>*_Nonnull)obstructions;

/**
 Removes registered friendly obstructions.

 This method will have no affect if called after the omid ad session has finished.

 @param obstructions  The friendly obstructions to be removed from the list of registered friendly obstructions.
*/
+ (void)removeFriendlyObstructions:(NSArray<UIView *>*_Nonnull)obstructions;

/**
 Removes all registered friendly obstructions.
 
 This method will have no affect if called after the omid ad session has finished.
*/
+ (void)removeAllFriendlyObstructions;

/**
 Updates the native view which is used for viewabililty tracking.
 If the view changes at a subsequent time due to a fullscreen expansion or for a similar reason, you should always update the View reference to whatever is appropriate at that time by calling this method.

 This method will have no affect if called after the omid ad session has finished.

 If an ad view is already registered for the current session, that ad view will be automatically unregistered and the new ad view will be registered in its place.
 @param adView The native view which should be registered for viewability tracking.
*/
+ (void)registerAdView:(UIView *_Nonnull)adView;

@end

