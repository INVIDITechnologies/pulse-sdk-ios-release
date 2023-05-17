//
//  OOPlayerState.h
//  Pulse
//
//  Created by Preti Verma on 2020-03-26.
//  Copyright © 2020 Ooyala. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 * List of supported video event player states.
 */
typedef NS_ENUM(NSInteger, OOPlayerState) {
    /** The player is collapsed in such a way that the video is hidden. The
     video may or may not still be progressing in this state, and sound may
     be audible. This refers specifically to the video player state on the
     page, and not the state of the browser window. */
    OOPlayerStateMINIMIZED,
    /** The player has been reduced from its original size. The video is still
     potentially visible. */
    OOPlayerStateCOLLAPSED,
    /** The player's default playback size. */
    OOPlayerStateNORMAL,
    /** The player has expanded from its original size. */
    OOPlayerStateEXPANDED,
    /** The player has entered fullscreen mode. */
    OOPlayerStateFULLSCREEN
};
