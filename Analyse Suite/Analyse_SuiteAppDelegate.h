//
//  Analyse_SuiteAppDelegate.h
//  Analyse Suite
//
//  Created by Wutzi on 14.03.11.
//  Copyright 2011 me. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface Analyse_SuiteAppDelegate : NSObject <NSApplicationDelegate> {
@private
	NSWindow *window;
}

@property (assign) IBOutlet NSWindow *window;

@end
