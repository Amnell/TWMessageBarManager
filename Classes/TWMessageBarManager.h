//
//  TWMessageBarManager.h
//
//  Created by Terry Worona on 5/13/13.
//  Copyright (c) 2013 Terry Worona. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  Three base message bar types. Their look & feel is defined within the MessageBarStyleSheet.
 */
typedef enum {
    TWMessageBarMessageTypeError,
    TWMessageBarMessageTypeSuccess,
    TWMessageBarMessageTypeInfo
} TWMessageBarMessageType;

@protocol TWMessageBarStyleSheet <NSObject>

/**
 *  Background color of message view.
 *
 *  @param type A MessageBarMessageType (error, information, success, etc).
 *
 *  @return UIColor istance representing the message view's background color.
 */
- (UIColor *)backgroundColorForMessageType:(TWMessageBarMessageType)type;

/**
 *  Bottom stroke color of message view.
 *
 *  @param type A MessageBarMessageType (error, information, success, etc).
 *
 *  @return UIColor istance representing the message view's bottom stroke color.
 */
- (UIColor *)strokeColorForMessageType:(TWMessageBarMessageType)type;

/**
 *  Icon image of the message view.
 *
 *  @param type A MessageBarMessageType (error, information, success, etc)
 *
 *  @return UIImage istance representing the message view's icon.
 */
- (UIImage *)iconImageForMessageType:(TWMessageBarMessageType)type;

@end

@interface TWMessageView : UIView

/**
 *  Adds the message to the display queue
 */
- (void)show;

/**
 *  Hides the message and removes it from the display queue
 */
- (void)hide;

@end

@interface TWMessageBarManager : NSObject

/**
 *  Singleton instance through which all presentation is managed.
 *
 *  @return MessageBarManager instance (singleton).
 */
+ (TWMessageBarManager *)sharedInstance;

/**
 *  An object conforming to the TWMessageBarStyleSheet protocol defines the message bar's look and feel.
 *  If no style sheet is supplied, a default class is provided on initialization (see implementation for details).
 */
@property (nonatomic, strong) NSObject<TWMessageBarStyleSheet> *styleSheet;

/**
 *  Returns a message with the supplied title, description and type (dictates color, stroke and icon).
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @return TWmessageView a TWMessageView instance
 */
- (TWMessageView *)messageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type;

/**
 *  Returns a message with the supplied title, description, type (dictates color, stroke and icon) & callback block.
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @param callback     Callback block to be executed if a message is tapped.
 *  @return TWmessageView a TWMessageView instance
 */
- (TWMessageView *)messageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type callback:(void (^)())callback;

/**
 *  Returns a message with the supplied title, description, type (dictates color, stroke and icon) & duration.
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @param duration     Default duration is 3 seconds, this can be overridden by supplying an optional duration parameter.
 *  @return TWmessageView a TWMessageView instance
 */
- (TWMessageView *)messageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type duration:(CGFloat)duration;

/**
 *  Returns a message with the supplied title, description, type (dictates color, stroke and icon), callback block & duration.
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @param duration     Default duration is 3 seconds, this can be overridden by supplying an optional duration parameter.
 *  @param callback     Callback block to be executed if a message is tapped.
 *  @return TWmessageView a TWMessageView instance
 */
- (TWMessageView *)messageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type duration:(CGFloat)duration callback:(void (^)())callback;

/**
 *  Shows a message with the supplied title, description and type (dictates color, stroke and icon).
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 */
- (void)showMessageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type;

/**
 *  Shows a message with the supplied title, description, type (dictates color, stroke and icon) & callback block.
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @param callback     Callback block to be executed if a message is tapped.
 */
- (void)showMessageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type callback:(void (^)())callback;

/**
 *  Shows a message with the supplied title, description, type (dictates color, stroke and icon) & duration.
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @param duration     Default duration is 3 seconds, this can be overridden by supplying an optional duration parameter.
 */
- (void)showMessageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type duration:(CGFloat)duration;

/**
 *  Shows a message with the supplied title, description, type (dictates color, stroke and icon), callback block & duration.
 *
 *  @param title        Header text in the message view.
 *  @param description  Description text in the message view.
 *  @param type         Type dictates color, stroke and icon shown in the message view.
 *  @param duration     Default duration is 3 seconds, this can be overridden by supplying an optional duration parameter.
 *  @param callback     Callback block to be executed if a message is tapped.
 */
- (void)showMessageWithTitle:(NSString *)title description:(NSString *)description type:(TWMessageBarMessageType)type duration:(CGFloat)duration callback:(void (^)())callback;

/**
 *  Returns the currently visible TWMessageView
 *
 *  @return TWMessageView Currently visibe TWMessageView, nil if none
 */
- (TWMessageView *)currentMessageView;

/**
 * Adds the given message to the queue and displays it when possible
 *
 * @param messageView   A TWmessageView instance
 */
- (void)showMessage:(TWMessageView *)messageView;

/**
 *  Hides the topmost message from view and removes all remaining messages in the queue (not animated).
 */
- (void)hideAll;

/**
 *  Removes a given TWMessageView from the queue. If it is visible it will be hidden and thus removed.
 *
 *  @param messageView A previously added message view currently visible or queued
 */
- (void)hideMessage:(TWMessageView *)messageView;

/**
 Updates the frame for the current displaying message view to acommodate for the statusbar
 
 @note In a perfect world we don't want to have to do this manually. But in the world of iOS
 we have to play by the rules. The statusbar appearance is not KVO-compliant, nor do
 we get any notifications except for when we're in a phonecall. So, without swizzling we have to do
 it manually
 */
- (void)updateMessageFrames;

@end

@interface UIDevice (Additions)

/**
 *  Determines if the device instance is running iOS 7 or later.
 *
 *  @return YES if the device instance is running an OS >= 7, otherwise NO.
 */
- (BOOL)isRunningiOS7OrLater;

@end
