//
//  INOmidFriendlyObstruction.h
//  Pulse
//
//  Created by Nic Henriksson on 2021-01-18.
//  Copyright © 2021 Invidi. All rights reserved.
//
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 Defines different types of friendly obstructions.
 */
typedef NS_ENUM(NSUInteger, INOmidFriendlyObstructionPurpose) {
    /**
     * Views related to interacting with a video (e.g. play/pause buttons)
     */
    INOmidFriendlyObstructionPurposeVIDEOCONTROLS,
    /**
     * Views relating to closing an ad (e.g. close button
     */
    INOmidFriendlyObstructionPurposeCLOSEAD,
    /**
     * Views that are not visibly obstructing the ad but may seem so due to technical limitations
     */
    INOmidFriendlyObstructionPurposeNOTVISIBLE,
    /**
     * Views that are obstructing for any purpose not already described.
     */
    INOmidFriendlyObstructionPurposeOTHER
};

/**
Class that defines a friendly obstruction.
*/
@interface INOmidFriendlyObstruction : NSObject

/**
 * The view to be excluded from all ad session viewability calculations.
 */
@property (nonatomic, assign) UIView *view;

/**
 * The purpose of why this obstruction was necessary.
 */
@property (nonatomic, assign) INOmidFriendlyObstructionPurpose purpose;

/**
 * An explanation for why this obstruction is part of the ad experience if not already obvious from the purpose. Can be nil. If not nil, must be 50 characters or less and only contain characers A-z, 0-9, or spaces.
 */
@property (nonatomic, copy) NSString *detailedReason;

/**
 * Initialise with the view and purpose of this obstruction.
 */
- (instancetype)initWithView:(UIView *)view purpose:(INOmidFriendlyObstructionPurpose)purpose;

/**
 * Initialise with the view, purpose and reason describing this obstruction.
 */
- (instancetype)initWithView:(UIView *)view purpose:(INOmidFriendlyObstructionPurpose)purpose detailedReason:(NSString *) detailedReason;

@end
