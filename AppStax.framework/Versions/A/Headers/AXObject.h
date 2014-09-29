
#import <Foundation/Foundation.h>
#import "AXQuery.h"

extern NSString * const AXObjectDidSave;



/** You use the AXObject class to create, save and load objects with the AppStax backend. 
 A thorough introduction and guide to using this service is available at [appstax.com/docs/](https://appstax.com/docs/iOS_Guide.html)
 
 Remember that you need to initialize your app with an app key with [AppStax setAppKey:] before
 using any of the methods in this class. Sign up at [appstax.com](http://appstax.com/) to obtain your key.
 */
@interface AXObject : NSObject

@property (readonly) NSDictionary *allProperties;
@property (readonly) NSString *collectionName;
@property (readonly) NSString *objectID;
@property (readonly) BOOL saved;

/// @name Creating new objects

/** Creates a new object.
 
 @param collectionName The collection the object will belong to.
 @return A new object instance.
 */
+ (AXObject *)create:(NSString *)collectionName;

/** Creates a new object with the given set of initial properties.
 
 @param collectionName The collection the object will belong to.
 @param properties Dictionary of initial property values.
 @return A new object instance.
 */
+ (AXObject *)create:(NSString *)collectionName properties:(NSDictionary *)properties;

/// @name Saving objects

/** Saves the object asyncronously.
 
 */
- (void)save;

/** Saves the object asyncronously.
 
 @param completion Completion handler called when the request has completed.
 */
- (void)save:(void(^)(NSError *error))completion;

/** Saves multiple asyncronously.
 
 @param objects Array of AXObject instances to save.
 @param completion Completion handler called when all save requests have completed
 */
+ (void)saveObjects:(NSArray *)objects completion:(void(^)(NSError *error))completion;

/// @name Loading objects

/** Loads all objects from a collection.
 
 @param collectionName Name of the collection.
 @param completion Completion handler called when the request has completed.
 */
+ (void)findAll:(NSString *)collectionName completion:(void(^)(NSArray *objects, NSError *error))completion;

/** Loads a single object from a collection.
 
 @param collectionName Name of the collection.
 @param objectID Id of the object to load.
 @param completion Completion handler called when the request has completed.
 */
+ (void)find:(NSString *)collectionName withId:(NSString *)objectID completion:(void(^)(AXObject *object, NSError *error))completion;

/** Query a collection for objects with specific property values.
 The returned objects have property values that match exactly to the propertyValues parameter.
 
 @param collectionName Name of the collection.
 @param propertyValues A dictionary where the keys are property names and the values are property values.
 @param completion Completion handler called when the request has completed.
 */
+ (void)find:(NSString *)collectionName with:(NSDictionary *)propertyValues completion:(void(^)(NSArray *objects, NSError *error))completion;

/** Search a collection for objects.
 In the returned objects at least one of the properties contain the value given for that property in the propertyValues parameter.
 
 @param collectionName Name of the collection.
 @param propertyValues A dictionary where the keys are property names and the values are values to search for.
 @param completion Completion handler called when the request has completed.
 */
+ (void)find:(NSString *)collectionName search:(NSDictionary *)propertyValues completion:(void(^)(NSArray *objects, NSError *error))completion;

/** Search a collection for objects, searching multiple properties for the same value.
 In the returned objects at least one of the properties contain the value given the searchString property.
 
 @param collectionName Name of the collection.
 @param searchString The string to search for.
 @param searchProperties Array of property names to search in.
 @param completion Completion handler called when the request has completed.
 */
+ (void)find:(NSString *)collectionName search:(NSString *)searchString properties:(NSArray *)searchProperties completion:(void(^)(NSArray *objects, NSError *error))completion;

/** Query a collection for objects, configuring the query in the queryBlock parameter.
 
 @param collectionName Name of the collection.
 @param queryBlock A block where you configure the query object.
 @param completion Completion handler called when the request has completed.
 */
+ (void)find:(NSString *)collectionName query:(void(^)(AXQuery *query))queryBlock completion:(void(^)(NSArray *objects, NSError *error))completion;

/** Query a collection for objects using a query string.
 You may write the query string by hand or configure an AXQuery object and use its queryString property as parameter to this method.
 
 @param collectionName Name of the collection.
 @param queryString The query string.
 @param completion Completion handler called when the request has completed.
 */
+ (void)find:(NSString *)collectionName queryString:(NSString *)queryString completion:(void(^)(NSArray *objects, NSError *error))completion;

/// @name Deleting objects

/** Deletes the object asyncronously.
 
 */
- (void)delete;

/** Deletes the object asyncronously.
 
 @param completion Completion handler called when the request has completed.
 */
- (void)delete:(void(^)(NSError *error))completion;

- (id)objectForKeyedSubscript:(id <NSCopying>)key;
- (void)setObject:(id)obj forKeyedSubscript:(id <NSCopying>)key;

@end
