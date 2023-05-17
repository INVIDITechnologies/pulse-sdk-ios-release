//
//  OOPulseVideoAd.h
//  Pulse
//
//  Created by Jacques du Toit on 11/11/15.
//  Copyright © 2015 Ooyala. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <Pulse/OOMediaFile.h>
#import <Pulse/OOPulseAdError.h>
#import <Pulse/OOPulseAd.h>
#import <Pulse/OOAdPricing.h>
#import <Pulse/OOAdSystem.h>
#import <Pulse/OOPlayerState.h>
#import <Pulse/OOPulseCompanionAd.h>
#import <Pulse/OOAdVerification.h>
#import <UIKit/UIKit.h>
    
@class VPCondition;
@class VPAd;
@class OOPulse;

/**
 *  This is the protocol for video ads owned by a `OOPulseSession`.
 *
 *  This protocol is used to notify the session about events
 *  regarding this ad, and provides access to relevant properties.
 *
 *  You must notify this object of the following events:
 *
 *  - The ad has started: `-[OOPulseVideoAd adStarted]`
 *  - The ad playback position has changed: `-[OOPulseVideoAd adPositionChanged:]`
 *  - The ad has played to completion: `-[OOPulseVideoAd adFinished]`
 *  - The ad failed to play: `-[OOPulseVideoAd adFailedWithError:]`
 *
 *  Depending on your application some of the other methods may need to be called
 *  in response to user interaction.
 *
 */
@protocol OOPulseVideoAd <OOPulseAd>

/**  @name Ad event notifications
*/

/**
 *  Notify the session that the ad has started playing.
 *
 *  This should only be called after your delegate has been instructed to play
 *  the ad through `-[OOPulseSessionDelegate startAdPlaybackWithAd:timeout:]`.
 */
- (void)adStarted;

/**  @name Ad event notifications
*/

/**
 *  Notify the session that the ad has started playing and report the player volume.
 *  The player volume is needed to make sure Open Measurement tracking is accurate.
 *
 *  This should only be called after your delegate has been instructed to play
 *  the ad through `-[OOPulseSessionDelegate startAdPlaybackWithAd:timeout:]` and the user-visible phase of the ad has begun.
 *
 *  @param playerVolume Player volume in a range between 0 and 1. Default value is 1.
 */
- (void)adStarted:(CGFloat)playerVolume;

/**
 *  Notify the session that the ad has played to completion.
 *
 *  After this, one of the following delegate methods may be triggered:
 *
 *  - `-[OOPulseSessionDelegate startAdPlaybackWithAd:timeout:]` - if there are more ads in this ad break
 *  - `-[OOPulseSessionDelegate startContentPlayback]` - if there are no more ads and the content has not finished
 *  - `-[OOPulseSessionDelegate sessionEnded]` - otherwise
 */
- (void)adFinished;

/**
 *  Notify the session that the ad was skipped by the user.
 *
 *  After this, one of the following delegate methods may be triggered:
 *
 *  - `-[OOPulseSessionDelegate startAdPlaybackWithAd:timeout:]` - if there are more ads in this ad break
 *  - `-[OOPulseSessionDelegate startContentPlayback]` - if there are no more ads and the content has not finished
 *  - `-[OOPulseSessionDelegate sessionEnded]` - otherwise
 */
- (void)adSkipped;

/**
 *  Notify the session that the ad playback position has changed, either as a result of seeking or normal playback.
 *
 *  This may trigger preloadNextAdWithAd through `-[OOPulseSessionDelegate preloadNextAdWithAd:]` if all of the conditions below are fulfilled:
 *  1. Preload next ad feature is enabled for your Pulse account.
 *  2. There are more ads to be played in the current ad break.
 *  3. Time to preload next ad has been reached. This means that the remaining duration of current ad is less than or equal to what has been configured for preloading next ad.
 *  4. preloadNextAd has not already been triggered for the ad.
 *
 *  @param position The ad position in seconds since start.
 */
- (void)adPositionChanged:(NSTimeInterval)position;

/**
 *  Notify the session that the ad has paused.
 */
- (void)adPaused;

/**
 *  Notify the session that the ad has resumed playback.
 */
- (void)adResumed;

/**
 *  Notify the session that, due to an error, the ad could not be played or that playback
 *  could not continue.
 *
 *  @param error The `OOPulseAdError` that best describes the problem.
 */
- (void)adFailedWithError:(OOPulseAdError)error;
/**
 * Notify all video listeners that the native video Player State has changed. This is related to viewability calculations when using OM SDK Integration.
 *
 * @param playerState The `OOPlayerState`  that the video player has entered into.
 */
- (void)playerStateChanged:(OOPlayerState)playerState;

/**Notify all video listeners that the native video player volume has changed.
 * This is related to viewability calculations when using OM SDK Integration.
 *
 * @param videoPlayerVolume from the native video player with a range between 0 and 1
 */
- (void)playerVolumeChanged:(CGFloat)videoPlayerVolume;

/**  @name Ad properties
*/

/**
 *  Returns an array of media files for this ad.
 *
 *  Your application should choose the best media file to display based on size
 *  bandwidth, and format considerations.
 *
 *  If none of the media files are supported by your video player, you should
 *  call `-[OOPulseVideoAd adFailedWithError:]` with
 *  `OOPulseAdError.OOPulseAdErrorNoSupportedMediaFile`.
 *
 *  @return A NSArray of `OOMediaFile` instances.
 */
- (NSArray<OOMediaFile*>*)mediaFiles;

/**
 * Determine whether or not a skip button for the ad may be displayed.
 *
 * If true, check the value of `-[OOPulseVideoAd skipOffset]`, which is the amount
 * of seconds from the start of the ad at which the button should first be displayed.
 *
 * When the viewer activates this button, call `-[OOPulseVideoAd adSkipped]`.
 */
- (BOOL)isSkippable;

/**
 * The amount of seconds from the start of the ad at which the button should first be displayed.
 *
 * If an `OOPulseVideoAd` is playing, and a call to `-[OOPulseVideoAd isSkippable]` returns YES,
 * show a skip button after this amount of seconds has passed.
 */
-(NSTimeInterval)skipOffset;

/**
 The ad variant type.
 @see `OOPulseAdVariant`
 */
- (OOPulseAdVariant)variant;

/**
 The ad id.
 */
- (NSString *)identifier;

/**
 Indicates whether the ad is ready to be displayed.
 */
- (BOOL)isReady;

/**
 The maximum time in seconds the SDK waits for a 'lazy' ad to load (including potential passback candidate requests).
 */
- (NSTimeInterval)maximumPreparationTime;

/**
 The maximum time in seconds the end user should be allowed to wait for an ad to load before the ad must be discarded.
 */
- (NSTimeInterval)startTimeout;

/**
 The candidate ad number in the passback chain.
 */
- (NSInteger)candidateNum;

/**
 The custom ad identifier set in the Ooyala Pulse UI.
 */
- (NSString *)customIdentifier;

/**
 The Identifier of the advertiser to which the ad belongs.
 */
- (NSString *)advertiserIdentifier;

/**
 The Identifier of the campaign to which the ad belongs; supplied by Ooyala Pulse.
 */
- (NSString *)campaignIdentifier;

/**
 The custom Identifier of the campaign to which the ad belongs; set in the Ooyala Pulse UI.
 */
- (NSString *)customCampaignIdentifier;

/**
 The Identifier of the goal to which the ad belongs; supplied by Ooyala Pulse.
 */
- (NSString *)goalIdentifier;

/**
 The custom Identifier of the goal to which the ad belongs; set in the Ooyala Pulse UI.
 */
- (NSString *)customGoalIdentifier;

/**
 Whether or not the ad is part of an exclusive campaign.
 */
- (BOOL)partOfAnExclusiveCampaign;

/**
 Whether or not to display a remaining time countdown when this ad is being displayed.
 */
- (BOOL)showCountdown;

/**
 Returns YES if this ad has passback ad sources available.
 */
- (BOOL)hasPassback;

/**
 A Boolean value that identifies a conditional ad. A value of true indicates that the ad is conditional and should be used in all cases where the inline executable unit (such as VPAID) is not an ad but is instead a framework for finding an ad; a value of false is the default value and indicates that an ad is available.
 */
- (BOOL)isConditionalAd;

/**
 A URL to any resource relating to an integrated survey.
 */
- (NSURL *)survey;

/**
 An array containing all the `OOAdSurvey` elements, containing any resource relating to an integrated survey.
 */
- (NSArray *)surveys;

/**
 A string that provides a common name for the ad.
 */
- (NSString *)title;

/**
 A string that provides the name of the advertiser as defined by the ad serving party.
 */
- (NSString *)advertiser;

/**
 A string value that describes a longer description of the ad.
 */
- (NSString *)adDescription;

/**
 Used to provide a value that represents a price that can be used by real-time bidding (RTB) systems.
 */
- (OOAdPricing *)adPricing;

/**
 An array of `OOAdCategory` objects containing the categories of the Ad and their responsible authorities.
 */
- (NSArray *)categories;

/**
 An array containing the `OOAdVerification` elements, which are used to initiate a controlled container where code can be executed for collecting data to verify ad playback details.
 */
- (NSArray<OOAdVerification *> *)adVerifications;

/**
 Bool that provides value for if omsdk is enabled
 */
- (BOOL)isOmsdkEnabled;
/**
 Information about the system that serves the ad.
 */
- (OOAdSystem *)adSystem;

/**
 *  Returns an array of companion banners for this ad.
 *
 *  Your application should choose the proper companion banner to display based on their
 *  zone identifier.
 *
 *  @return A NSArray of objects conforming to the `OOPulseCompanionAd` protocol.
 */
- (NSArray<id<OOPulseCompanionAd>>*)companions;

/**
* Returns condition of ad describe the conditions for when a particular VPInsertionPoint should be triggered..
* @return the condition
*/
- (VPCondition *)adCondition;

@end
