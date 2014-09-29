
#import <Foundation/Foundation.h>


/** You use AXQuery together with [AXObject find:query:completion:] to load objects from your Appstax Data Store.
 To learn more about object queries we recommend reading the guide found at [appstax.com/docs/](https://appstax.com/docs/iOS_Guide.html#quering-objects)
 */
@interface AXQuery : NSObject

@property (readonly) NSString *queryString;

/** Creates an empty query object.
 */
+ (instancetype)query;

/** Creates a query object with the specified query string as its first constraint.
 
 @param queryString The query string.
 */
- (instancetype)initWithQueryString:(NSString *)queryString;

/// @name String constraints

/** Add a constraint to match a string property to an exact string value.
 
 @param property Name of a string property.
 @param value String value to match.
 */
- (void)string:(NSString *)property equals:(NSString *)value;

/** Add a constraint to match a string property when its value contains the given value.
 
 @param property Name of a string property.
 @param value String to look for in the property value.
 */
- (void)string:(NSString *)property contains:(NSString *)value;

@end
