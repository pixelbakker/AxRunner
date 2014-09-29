
#import <Foundation/Foundation.h>
#import "AXLoginViews.h"

@class UIView;


/** You use the AXUser class to interact with the user service from AppStax.
 A thorough introduction and guide to handling users is available at [appstax.com/docs/](https://appstax.com/docs/iOS_Guide.html)
 
 Remember that you need to initialize your app with an app key with [AppStax setAppKey:] before
 using any of the methods in this class. Sign up at [appstax.com](http://appstax.com/) to obtain your key.
 */
@interface AXUser : NSObject

/** Username */
@property (readonly) NSString *username;

/// @name Saving user data

/** Saves the user object asyncronously.
 
 */
- (void)save;

/** Saves the user object asyncronously.
 
 @param completion Completion handler called when the request has completed.
 */
- (void)save:(void(^)(NSError *error))completion;

- (id)objectForKeyedSubscript:(id <NSCopying>)key;
- (void)setObject:(id)obj forKeyedSubscript:(id <NSCopying>)key;

/// @name Getting users to sign up and log in

/** Makes sure your app has a logged in user. Shows a signup/login screen if neccesary.
 
 If a user is already logged in, the completion handler is called with the value of [AXUser currentUser].
 
 If no currentUser is found, the sugnup/login user interface is shown. The completion handler is called after the signup/login is successful.
 
 @param completion Completion handler called when a logged in user exists.
 
 */
+ (void)requireLogin:(void(^)(AXUser *user))completion;

/** Same as requireLogin: but with customized appearance.
 
 The loginViews block is used to change properties of the login an signup backgrounds, or to load new background views from a nib.
 
    [AXUser requireLogin:^(AXUser *user) {
 
    } withCustomViews:^(AXLoginViews *views) {
        views.signup.backgroundColor = [UIColor lightGrayColor];
        views.login.backgroundColor  = [UIColor lightGrayColor];
    }];
 
 For more examples see the [Appstax Guide](http://www.appstax.com/docs/iOS_Guide.html)
 
 @param completion Completion handler called when a logged in user exists.
 @param loginViews Apply view customization within this block.
 @see AXLoginViews
 */
+ (void)requireLogin:(void(^)(AXUser *))completion withCustomViews:(void(^)(AXLoginViews *views))loginViews;

/** Returns the currently logged in user.

 @returns The currently logged in user.
 
 */
+ (AXUser *)currentUser;

/** Logs out the current user
 */

+ (void)logout;


/// @name Custom user handling

/** Sign up a new user with username and password.
 
 @param username Username
 @param password Password
 @param completion Completion handler called when the signup request completes.
 */
+ (void)signupWithUsername:(NSString *)username password:(NSString *)password completion:(void(^)(AXUser *user, NSError *error))completion;

/** Log in a registered user with username and password.
 
 @param username Username
 @param password Password
 @param completion Completion handler called when the login request completes.
 */
+ (void)loginWithUsername:(NSString *)username password:(NSString *)password completion:(void(^)(AXUser *user, NSError *error))completion;


@end
