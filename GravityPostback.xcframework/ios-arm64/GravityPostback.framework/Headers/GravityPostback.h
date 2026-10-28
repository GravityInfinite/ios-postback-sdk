//
//  GravityPostback.h
//  GravityPostback
//
//  Created by leo on 2026/9/30.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface GravityPostbackConfig : NSObject

@property(nonatomic,assign)BOOL enableTapTap;
@property(nonatomic,assign)BOOL enableByteDance;
@property(nonatomic,assign)BOOL enableGDT;


@property(nonatomic,assign)BOOL enableLog;
@property(nonatomic,assign)BOOL enableIdfa;
@property(nonatomic,assign)BOOL isPortrait;

@property(nonatomic,strong)NSString * _Nullable gravityChannel;
@property(nonatomic,strong)NSString * _Nullable gravityClientId;
@property(nonatomic,strong)NSString * _Nullable gravityClientName;
@property(nonatomic,strong)NSString * _Nullable gravityAccessToken;
@property(nonatomic,strong)NSString * _Nullable gravityCaid;
@property(nonatomic,assign)BOOL gravityNeedReturnAttribution;

@property(nonatomic,strong)NSString * _Nullable gdtUserActionSetId;
@property(nonatomic,strong)NSString * _Nullable gdtAppSecretKey;

// TapTap 配置
@property(nonatomic,assign)BOOL tapNeedInit;        // 是否由本 SDK 初始化 TapTapSdk（外部已初始化时设 NO，避免重复 init）
@property(nonatomic,assign)BOOL tapNeedAnalytics;   // 是否启用本 SDK 的 TapDB 数据分析上报（外部接入 TapTap 但不需要统计时设 NO）
@property(nonatomic,strong)NSString * _Nullable tapClientId;
@property(nonatomic,strong)NSString * _Nullable tapClientToken;
@property(nonatomic,strong)NSString * _Nullable tapAnalyticsChannel;
@property(nonatomic,assign)BOOL tapAutoIAPEventEnabled;

@property(nonatomic,strong)NSMutableArray * _Nullable dryRunEventNames;

@end


typedef NS_ENUM(NSInteger, GravityPostbackModuleType) {
    USER,//用户
    POSTBACK,//postback
    ALL_NO_USER,//除USER外
};


typedef NS_ENUM(NSInteger, GravityPostbackFunctionType) {
    // ===================== 统计/数据分析事件（PulseTrack 分发，对接引力引擎等统计渠道） =====================
    STAT_FLUSH,                 // 立即上报缓存事件（flush）
    STAT_USER_SET,              // 用户属性：覆盖写（user_set）
    STAT_USER_SETONCE,          // 用户属性：首次设置，不覆盖（user_setOnce）
    STAT_USER_INCREMENT,        // 用户属性：数值累加（user_increment）
    STAT_USER_MAX,              // 用户属性：取最大值（user_max）
    STAT_USER_MIN,              // 用户属性：取最小值（user_min）
    STAT_USER_APPEND,           // 用户属性：数组追加（user_append）
    STAT_USER_UNIQAPPEND,       // 用户属性：数组去重追加（user_uniqAppend）
    STAT_USER_DELETE,           // 用户属性：删除用户，清空（user_delete）
    STAT_USER_UNSET,            // 用户属性：重置（删除）指定属性（user_unset）
    STAT_SUPER_PROPERTIES,      // 公共事件属性，全局生效（setSuperProperties）
    UNSET_SUPER_PROPERTIES,      // 移除某公共事件属性，全局生效（setSuperProperties）
    CLEAR_SUPER_PROPERTIES,      // 清除所有公共事件属性，全局生效（setSuperProperties）

    // ===================== 统计/数据分析事件：引力引擎封装的 track 事件（账号/支付/广告） =====================
    TRACK,
    TRACK_REGISTER,        // 注册事件（trackRegisterEvent）
    TRACK_LOGIN,           // 登录事件（trackLoginEvent）
    TRACK_LOGOUT,          // 登出事件（trackLogoutEvent）
    TRACK_SHARE,           // 分享事件（trackShareEvent，对应 ActionUtils.onShare）
    TRACK_PAY,             // 付费事件（trackPayEvent）
    TRACK_WITHDRAW,        // 提现事件（trackWithdrawEvent）
    TRACK_AD_LOAD,         // 广告加载事件（trackAdLoadEvent）
    TRACK_AD_SHOW,         // 广告展示事件（trackAdShowEvent）
    TRACK_AD_SKIP,         // 广告跳过事件（trackAdSkipEvent）
    TRACK_AD_CLICK,        // 广告点击事件（trackAdClickEvent）
    TRACK_AD_PLAY_START,   // 广告播放开始事件（trackAdPlayStartEvent）
    TRACK_AD_PLAY_END,     // 广告播放结束事件（trackAdPlayEndEvent）

    // ===================== 统计/数据分析事件：广点通（腾讯数智）标准行为事件 =====================
    TRACK_VIEW_CONTENT,        // 内容浏览事件（trackViewContentEvent，对应 ActionUtils.onViewContent）
    TRACK_ADD_TO_CART,         // 加入购物车事件（trackAddToCartEvent，对应 ActionUtils.onAddToCart）
    TRACK_CHECKOUT,            // 下单/结账事件（trackCheckoutEvent，对应 ActionUtils.onCheckout）
    TRACK_BIND_ACCOUNT,        // 绑定账号事件（trackBindAccountEvent，对应 ActionUtils.onBindAccount）
    TRACK_CREATE_ROLE,         // 创建角色事件（trackCreateRoleEvent，对应 ActionUtils.onCreateRole）
    TRACK_UPDATE_LEVEL,        // 更新等级事件（trackUpdateLevelEvent，对应 ActionUtils.onUpdateLevel）
    TRACK_RATE_APP,            // 应用评分事件（trackRateAppEvent，对应 ActionUtils.onRateApp）
    TRACK_QUEST_FINISH,        // 任务完成事件（trackQuestFinishEvent，对应 ActionUtils.onQuestFinish）
    TRACK_ADD_PAYMENT_CHANNEL, // 添加支付渠道事件（trackAddPaymentChannelEvent，对应 ActionUtils.onAddPaymentChannel）
};

@protocol GravityPostbackBaseDelegate <NSObject>

- (void)initSDK:(GravityPostbackConfig * _Nullable)config;

- (void)application:(UIApplication *_Nullable)application didFinishLaunchingWithOptions:(NSDictionary *_Nullable)launchOptions ;

- (void)scene:(UIScene *_Nullable)scene willConnectToSession:(UISceneSession *_Nullable)session options:(UISceneConnectionOptions *_Nullable)connectionOptions  API_AVAILABLE(ios(13.0));

- (void)application:(UIApplication *_Nullable)app openURL:(NSURL *_Nullable)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *_Nullable)options ;
- (void)scene:(UIScene *_Nullable)scene openURLContexts:(NSSet<UIOpenURLContext *> *_Nullable)URLContexts  API_AVAILABLE(ios(13.0));

- (void)applicationDidBecomeActive:(UIApplication *_Nullable)application ;
- (void)application:(UIApplication * _Nullable)application continueUserActivity:(NSUserActivity *_Nullable) userActivity restorationHandler:(void (^_Nullable)(NSArray<id<UIUserActivityRestoring>> * _Nullable)) restorationHandler ;

- (NSObject*_Nullable)callModule:(GravityPostbackModuleType) fromModuleType to:(GravityPostbackModuleType)toModuleType func:(GravityPostbackFunctionType)functionType properties:(NSArray *_Nullable)properties;
- (NSObject*_Nullable)callModule:(NSString *_Nullable) fromSdkId to:(NSString*_Nullable)toSdkId funName:(NSString*_Nullable)functionName func:(GravityPostbackFunctionType)functionType properties:(NSArray *_Nullable)properties;

@end


@interface GravityPostbackLog : NSObject
+(void)setDebug:(BOOL)debug;
+(void)i:(NSString *_Nullable)msg;
+(void)i:(NSString *_Nullable)tag m:(NSString *_Nullable)msg;
+(void)e:(NSString *_Nullable)msg;
+(void)e:(NSString *_Nullable)tag m:(NSString *_Nullable)msg;
+(void)w:(NSString *_Nullable)msg;
+(void)w:(NSString *_Nullable)tag m:(NSString *_Nullable)msg;
@end


@interface GravityPostback : NSObject
+ (void)initSDK:(GravityPostbackConfig * _Nullable)config;

+ (void)application:(UIApplication *_Nullable)application didFinishLaunchingWithOptions:(NSDictionary *_Nullable)launchOptions ;

+ (void)scene:(UIScene *_Nullable)scene willConnectToSession:(UISceneSession *_Nullable)session options:(UISceneConnectionOptions *_Nullable)connectionOptions  API_AVAILABLE(ios(13.0));

+ (void)application:(UIApplication *_Nullable)app openURL:(NSURL *_Nullable)url options:(NSDictionary<UIApplicationOpenURLOptionsKey,id> *_Nullable)options ;
+ (void)scene:(UIScene *_Nullable)scene openURLContexts:(NSSet<UIOpenURLContext *> *_Nullable)URLContexts  API_AVAILABLE(ios(13.0));

+ (void)applicationDidBecomeActive:(UIApplication *_Nullable)application ;
+ (void)application:(UIApplication * _Nullable)application continueUserActivity:(NSUserActivity *_Nullable) userActivity restorationHandler:(void (^_Nullable)(NSArray<id<UIUserActivityRestoring>> * _Nullable)) restorationHandler ;

+ (void)flush;
+ (void)userSet:(NSDictionary*_Nullable)properties;
+ (void)userUnset:(NSString*_Nullable)key;
+ (void)userSetOnce:(NSDictionary*_Nullable)properties;
+ (void)userIncrement:(NSString*_Nullable)key value:(NSNumber *_Nullable)value;
+ (void)userIncrement:(NSDictionary*_Nullable)properties;
+ (void)userMax:(NSDictionary*_Nullable)properties;
+ (void)userMin:(NSDictionary*_Nullable)properties;
+ (void)userAppend:(NSDictionary*_Nullable)properties;
+ (void)userUniqAppend:(NSDictionary*_Nullable)properties;
+ (void)userDelete;
+ (void)setSuperProperties:(NSDictionary*_Nullable)properties;
+ (void)unsetSuperProperties:(NSString*_Nullable)key;
+ (void)clearSuperProperties;

+ (void)track:(NSString*_Nullable)eventName properties:(NSDictionary*_Nullable)properties;
+ (void)track:(NSString*_Nullable)eventName properties:(NSDictionary*_Nullable)properties otherParams:(NSDictionary*_Nullable)otherParams;
+ (void)track:(NSString*_Nullable)eventName otherParams:(NSDictionary*_Nullable)otherParams;
+ (void)track:(NSString*_Nullable)eventName;
+ (void)trackRegisterEvent:(NSDictionary*_Nullable)otherParams;
+ (void)trackRegisterEvent;
+ (void)trackLoginEvent:(NSDictionary*_Nullable)otherParams;
+ (void)trackLoginEvent;
+ (void)trackLogoutEvent:(NSDictionary*_Nullable)otherParams;
+ (void)trackLogoutEvent;
+ (void)trackShareEvent:(NSDictionary*_Nullable)otherParams;
+ (void)trackShareEvent;

+ (void)trackPayEventWithAmount:(NSNumber *_Nullable)payAmount withPayType:(NSString *_Nullable)payType withOrderId:(NSString *_Nullable)orderId withPayReason:(NSString *_Nullable)payReason withPayMethod:(NSString *_Nullable)payMethod;
+ (void)trackPayEventWithAmount:(NSNumber *_Nullable)payAmount withPayType:(NSString *_Nullable)payType withOrderId:(NSString *_Nullable)orderId withPayReason:(NSString *_Nullable)payReason withPayMethod:(NSString *_Nullable)payMethod otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackWithdrawEvent:(NSNumber *_Nullable)payAmount withPayType:(NSString *_Nullable)payType withOrderId:(NSString *_Nullable)orderId withPayReason:(NSString *_Nullable)payReason withPayMethod:(NSString *_Nullable)payMethod;
+ (void)trackWithdrawEvent:(NSNumber *_Nullable)payAmount withPayType:(NSString *_Nullable)payType withOrderId:(NSString *_Nullable)orderId withPayReason:(NSString *_Nullable)payReason withPayMethod:(NSString *_Nullable)payMethod otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackAdLoadEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType;
+ (void)trackAdLoadEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackAdShowEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm;
+ (void)trackAdShowEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackAdSkipEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm;
+ (void)trackAdSkipEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackAdClickEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm;
+ (void)trackAdClickEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackAdPlayStartEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm;
+ (void)trackAdPlayStartEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm otherParams:(NSDictionary*_Nullable)otherParams;

+ (void)trackAdPlayEndEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm withDruation:(NSNumber *_Nullable)duration withIsPlayOver:(BOOL)isPlayOver;
+ (void)trackAdPlayEndEventWithUninType:(NSString *_Nullable)adUnionType withPlacementId:(NSString *_Nullable)adPlacementId withSourceId:(NSString *_Nullable)adSourceId withAdType:(NSString *_Nullable)adType withAdnType:(NSString *_Nullable)adAdnType withEcpm:(NSNumber *_Nullable)ecpm withDruation:(NSNumber *_Nullable)duration withIsPlayOver:(BOOL)isPlayOver otherParams:(NSDictionary*_Nullable)otherParams;

//gdt
+ (void)trackViewContentEvent:(NSString*_Nullable)type name:(NSString*_Nullable)name idstr:(NSString*_Nullable)idstr;
+ (void)trackAddToCartEvent:(NSString*_Nullable)type name:(NSString*_Nullable)name idstr:(NSString*_Nullable)idstr number:(NSNumber *_Nullable)number success:(BOOL)success;
+ (void)trackCheckoutEvent:(NSString*_Nullable)type name:(NSString*_Nullable)name idstr:(NSString*_Nullable)idstr number:(NSNumber *_Nullable)number isVirtualCurrency:(BOOL)isVirtualCurrency virtualCurrencyType:(NSString*_Nullable)virtualCurrencyType currency:(NSString*_Nullable)currency success:(BOOL)success;
+ (void)trackBindAccountEvent:(NSString*_Nullable)method success:(BOOL)success;
+ (void)trackCreateRoleEvent:(NSString*_Nullable)role;
+ (void)trackUpdateLevelEvent:(NSNumber *_Nullable)level;
+ (void)trackRateAppEvent:(NSNumber *_Nullable)value;
+ (void)trackQuestFinishEvent:(NSString*_Nullable)type name:(NSDictionary*_Nullable)name idstr:(NSDictionary*_Nullable)idstr desc:(NSDictionary*_Nullable)desc number:(NSNumber *_Nullable)number success:(BOOL)success;
+ (void)trackAddPaymentChannelEvent:(NSString*_Nullable)channel success:(BOOL)success;

+ (NSObject*_Nullable)callModule:(GravityPostbackModuleType) fromModuleType to:(GravityPostbackModuleType)toModuleType func:(GravityPostbackFunctionType)functionType properties:(NSArray *_Nullable)properties;
+ (NSObject*_Nullable)callModule:(NSString *_Nullable) fromSdkId to:(NSString*_Nullable)toSdkId funName:(NSString*_Nullable)functionName func:(GravityPostbackFunctionType)functionType properties:(NSArray *_Nullable)properties;
@end
