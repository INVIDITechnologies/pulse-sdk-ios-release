//
//  OORequestSettings.h
//  Pulse
//
//  Created by Jacques du Toit on 20/04/15.
//  Copyright (c) 2015 Ooyala. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 Options for types you can set in the `OORequestSettings.insertionPointFilter`
 property. These determine when the received ads are to be played.
 */
typedef NS_OPTIONS(NSUInteger, OOInsertionPointType) {
  /// The default, which will include all types.
  OOInsertionPointTypeAll              = 0,
  /// Request ads to be played before the content, or 'preroll' ads.
  OOInsertionPointTypeOnBeforeContent  = 1 << 0,
  /**
   Request midroll ads and/or overlay ads, to be played at the positions
   specified in linearPlaybackPositions and nonlinearPlaybackPositions
   respectively.
   */
  OOInsertionPointTypePlaybackPosition = 1 << 1,
  /// Request ads to be played after the content, or 'postroll' ads.
  OOInsertionPointTypeOnContentEnd     = 1 << 2,
  /// Request ads to be played when the content is paused.
  OOInsertionPointTypeOnPause          = 1 << 3,
  /**
   Request overlay ads to be displayed; based on the content duration, which
   must which must be specified as well.
  */
  OOInsertionPointTypePlaybackTime     = 1 << 4
};


/**
 Ad break positions which can be read from `OOPulseAdBreak`.
 */
typedef NS_ENUM(NSUInteger, OOAdBreakType) {
  /// The ad break plays before the main content.
  PREROLL,
  /// The ad break plays during the main content.
  MIDROLL,
  /// The ad break plays at the end of the main content.
  POSTROLL,
};

/**
Modes you can set in the `OORequestSettings.seekMode` property which determine
how the session behaves when a viewer seeks past one or more midroll ad breaks.
 */
typedef NS_ENUM(NSUInteger, OOSeekMode) {
  /// Do not enforce midroll ad breaks to be played. This is the default.
  IGNORE = 0,
  /// If the viewer seeks past one or more ad breaks, the first one is played
  /// before content resumes.
  PLAY_FIRST_AD = 1,
  /// If the viewer seeks past one or more ad breaks, the last one is played
  /// before content resumes.
  PLAY_LAST_AD = 2,
  /// If the viewer seeks past one or more ad breaks, all of them are played
  /// before content resumes.
  PLAY_ALL_ADS = 3
};

/**
Live options you can set in the `OORequestSettings.liveParameters` property,
used to disable certain tracking, secondary lookup requests,
real-time bidding requests, and/or cookie syncing for a live event.
 */
typedef NS_ENUM(NSUInteger, OOLive){
  /// Turn off all tracking (except for impression and click-through tracking),
  /// session lookup requests, location lookup request, and real-time bidding
  /// requests.
  DISABLE_ALL = 0,
  /// Turn off everything else except all tracking.
  ALL_TRACKINGS = 1,
  /// Turn off everything else except session lookup request.
  SESSION_LOOKUP = 2,
  /// Turn off everything else except location lookup request.
  LOCATION_LOOKUP = 3,
  /// Turn off everything else except  real-time bidding requests and their
  /// associated cookie syncing.
  REAL_TIME_BIDDING = 4
};

/**
 Settings about the environment in which the ad will play.
 */
@interface OORequestSettings : NSObject


- (id)copyExistingProperties:(OORequestSettings *)sourceRequestSetting
     OverrrideRequestSetting:(OORequestSettings *)overrideRs;

/**
 Height in pixels of the video area where ads will be shown.
 */
@property (nonatomic, assign) NSInteger height;

/**
 Width in pixels of the video area where ads will be shown.
 */
@property (nonatomic, assign) NSInteger width;

/**
 The maximum bitrate of the media files in the ad response.
 */
@property (nonatomic, assign) NSInteger maxBitRate;

/**
 The advertising identifier unique for each iOS device.
 If RTB ads are configured in Pulse, this information will be forwarded to the
 DSP.
 */
@property (nonatomic, copy) NSString *IDFA;

/**
 The id of the application using this SDK in the format "A1B2C3D4E5.com.domainame.applicationname".
 If RTB ads are configured in Pulse, this information will be forwarded to the DSP.
 */
@property (nonatomic, copy) NSString *applicationID;

/**
 The name of the application using this SDK. An example would be: "pulseplayer".
 If RTB ads are configured in Pulse, this information will be forwarded to the DSP.
 */
@property (nonatomic, copy) NSString *applicationName;

/**
 The version of the application using this SDK. An example would be: "1.0.0".
 If RTB ads are configured in Pulse, this information will be forwarded to the DSP.
 */
@property (nonatomic, copy) NSString *applicationVersion;

/**
 The bundle id of the application using this SDK, in the format "com.domainname.applicationname"
 If RTB ads are configured in Pulse, this information will be forwarded to the DSP.
 */
@property (nonatomic, copy) NSString *applicationBundle;

/**
 The App Store URL where you can download the application using this SDK. An example would be: "https://itunes.apple.com/us/app/keynote/id361285480?mt=8"
 If RTB ads are configured in Pulse, this information will be forwarded to the DSP.
 */
@property (nonatomic, copy) NSString *storeUrl;

/**
 Pass in the user's URL safe and base64 encoded consent string related to GDPR regulations, which may be obtained through the Mobile In-App Consent Management Provider (CMP) API.
 This string is built up according to the data structure developed by the GDPR Consent Working Group under the auspices of IAB Europe.
 The data structure specification can be found at [Consent string and vendor list format](https://github.com/InteractiveAdvertisingBureau/GDPR-Transparency-and-Consent-Framework/blob/master/TCFv2/IAB%20Tech%20Lab%20-%20Consent%20string%20and%20vendor%20list%20formats%20v2.md).
 For more information on the API, refer to [Mobile In-App Consent APIs](https://github.com/InteractiveAdvertisingBureau/GDPR-Transparency-and-Consent-Framework/blob/master/Mobile%20In-App%20Consent%20APIs%20v1.0%20Final.md).
 */
@property (nonatomic, copy) NSString *gdprConsentString;

/**
 Set to true if the ad request is subject to GDPR regulations. See [Implementation Guidelines](https://github.com/InteractiveAdvertisingBureau/GDPR-Transparency-and-Consent-Framework/blob/master/TCFv2/TCF-Implementation-Guidelines.md) for implementation guidelines.
 */
@property (nonatomic, assign) BOOL enableGdpr;

/**
 Set to true if you are passing in personal information when creating the ad request to Pulse. One of the locations where it is possible to pass in personal information is in the `OOContentMetadata.customParameters`.
 */
@property (nonatomic, assign) BOOL gdprPersonalDataIncluded;

/**
 An array of numbers which defines points in time when linear ads should be shown.
 */
@property (nonatomic, copy) NSArray *linearPlaybackPositions;

/**
 Overrides the maximum amount of time the player or integration should wait for the ad to start playback before reporting inventory.
 */
@property (nonatomic, assign) double startAdTimeout;

/**
 Overrides the maximum amount of time the player or integration should wait to unwrap and load a third party ad before reporting inventory.
 */
@property (nonatomic, assign) double thirdPartyTimeout;

/**
 Overrides the maximum amount of time the passback player should wait to find a working ad in the passback chain before moving to the last ad in the chain or reporting inventory.
 */
@property (nonatomic, assign) double totalPassbackTimeout;

/**
 <p><strong>DEPRECATED!</strong> Overrides the number of the ad break targeted by the ad request. Should be Positive Integer.</p>
 */
@property (nonatomic, assign) NSInteger breakNumber __attribute__((deprecated("breakNumber is deprecated and has been replaced by midrollBreakNumber")));

/**
 Overrides the number of the midroll ad break targeted by the ad request. Should be Positive Integer.
 */
@property (nonatomic, assign) NSInteger midrollBreakNumber;

/**
 An array of numbers which defines points in time when non-linear ads should be shown.
 */
@property (nonatomic, copy) NSArray *nonlinearPlaybackPositions;

/**
 A bitmask that determines which kinds of insertion points will be requested.
 If not set, all types will be requested.
 */
@property (nonatomic, assign) OOInsertionPointType insertionPointFilter;

/**
 Overrides the HTTP header's referrer property
 */
@property (nonatomic, copy) NSURL *referrerUrl;

/**
 The maximum duration in seconds of linear ad breaks.
 */
@property (nonatomic, assign) NSInteger maxLinearBreakDuration;

/**
 The minimum duration in seconds of linear ad breaks.
 */
@property (nonatomic, assign) NSInteger minLinearBreakDuration;

/**
 Indicates whether all the media files/assets for an ad should be returned.
 If true, the assets will not be filtered out based on the user agent.
 */
@property (nonatomic, assign) BOOL assetFilteringDisabled;

/**
 Indicates whether cache busting is enforced on all tracking request URLs.
 */
@property (nonatomic, assign) BOOL enforceCacheBusting;

/**
 Determines the Pulse SDK's behaviour when the viewer seeks past one or more ad breaks.
 If not set, the behaviour defaults to the `OOSeekMode.IGNORE`.
 */
@property (nonatomic, assign) OOSeekMode seekMode;

/**
 A list of live parameters indicating which behaviours should be disabled for a live event.
 If an empty list is set, the behaviour defaults to the `OOLive.DISABLE_ALL`.
 Notice that if all parameters are sent at once, then no action would be taken, i.e DISABLE_ALL would disable everything and other parameters would re-enable them.
 */
@property (nonatomic, strong) NSMutableArray<NSNumber *> *liveParameters;

@end
