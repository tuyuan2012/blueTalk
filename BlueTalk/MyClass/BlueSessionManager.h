//
//  BlueSessionManager.h
//  BlueTalk
//
//  Created by user on 15-4-8.
//  Copyright (c) 2015年 YangPeiQiu. All rights reserved.
//

#import <Foundation/Foundation.h>

@import MultipeerConnectivity;

@interface BlueSessionManager : NSObject

/*
 基本知识必须了解的
 
 MCAdvertiserAssistant   //可以接收，并处理用户请求连接的响应。没有回调，会弹出默认的提示框，并处理连接。
 MCNearbyServiceAdvertiser //可以接收，并处理用户请求连接的响应。但是，这个类会有回调，告知有用户要与您的设备连接，然后可以自定义提示框，以及自定义连接处理。
 MCNearbyServiceBrowser  //用于搜索附近的用户，并可以对搜索到的用户发出邀请加入某个会话中。
 MCPeerID //这表明是一个用户
 MCSession //启用和管理Multipeer连接会话中的所有人之间的沟通。 通过Sesion，给别人发送数据。
 
 */
@property(strong, nonatomic, readonly) NSArray *connectedPeers;

@property(strong, nonatomic, readonly) MCSession *session;

@property(nonatomic, readonly, getter = isConnected) BOOL connected;

@property(strong, nonatomic) NSDictionary *discoveryInfo; // 发现设备的特征

@property(strong, nonatomic, readonly) MCPeerID *firstPeer; // 第一个连接的 用户

/**
 * The service type provided for browsing and advertising.
 * This should be a short text string that describes the
 * app's networking protocol. Should be something
 * in the form of `tjl_appname`.
 */
@property(strong, nonatomic) NSString *serviceType;


/*
 初始化一个 假设的用户名字
 */
- (instancetype)__attribute__((nonnull(1)))initWithDisplayName:(NSString *)displayName;


- (void)browseForProgrammaticDiscovery;


- (void)advertiseForBrowserViewController;


- (void)advertiseForProgrammaticDiscovery;





- (void)didReceiveInvitationFromPeer:(void (^)(MCPeerID *peer, NSData *context))invite;


- (NSError *)sendDataToAllPeers:(NSData *)data;





- (NSError *)sendData:(NSData *)data toPeers:(NSArray *)peers;


- (NSError *)sendData:(NSData *)data toPeers:(NSArray *)peers withMode:(MCSessionSendDataMode)mode;


- (void)receiveDataOnMainQueue:(BOOL)mainQueue block:(void (^)(NSData *data, MCPeerID *peer))dataBlock;


- (NSProgress *)sendResourceWithName:(NSString *)name atURL:(NSURL *)url toPeer:(MCPeerID *)peer complete:(void (^)(NSError *error))compelete;


- (void)receiveFinalResourceOnMainQueue:(BOOL)mainQueue complete:(void (^)(NSString *name, MCPeerID *peer, NSURL *url, NSError *error))block;


- (void)startReceivingResourceOnMainQueue:(BOOL)mainQueue block:(void (^)(NSString *name, MCPeerID *peer, NSProgress *progress))block;


- (NSOutputStream *)streamWithName:(NSString *)name toPeer:(MCPeerID *)peerID error:(NSError * __autoreleasing *)error;


- (void)didReceiveStreamFromPeer:(void (^)(NSInputStream *inputStream, MCPeerID *peer, NSString *streamName))streamBlock;

- (void)peerConnectionStatusOnMainQueue:(BOOL)mainQueue block:(void (^)(MCPeerID *peer, MCSessionState state))status;


- (void)browseWithControllerInViewController:(UIViewController *)controller connected:(void (^)(void))connected canceled:(void (^)(void))cancelled;


- (void)didFindPeerWithInfo:(void (^)(MCPeerID *peer, NSDictionary *info))found;


- (void)connectToPeer:(BOOL)connect;

// 邀请其他设备连接
- (void)invitePeerToConnect:(MCPeerID *)peer connected:(void (^)(void))connected;


- (void)disconnectSession;

// 停止打开自己
- (void)stopAdvertising;

// 停止扫描
- (void)stopBrowsing;



@end
// 版权属于原作者
// http://code4app.com (cn) http://code4app.net (en)
// 发布代码于最专业的源码分享网站: Code4App.com