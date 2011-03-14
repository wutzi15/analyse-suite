//
//  Analyse_SuiteAppDelegate.m
//  Analyse Suite
//
//  Created by Wutzi on 14.03.11.
//  Copyright 2011 me. All rights reserved.
//

#import "Analyse_SuiteAppDelegate.h"


@implementation Analyse_SuiteAppDelegate

@synthesize ch_rec;
@synthesize ch_plot;

@synthesize ch_wl;
@synthesize ch_peak;
@synthesize tx_ftp;
@synthesize tx_dir;
@synthesize tx_files;

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	[tx_files registerForDraggedTypes:[NSArray arrayWithObject:NSPasteboardTypeTabularText]];
	[tx_dir registerForDraggedTypes:[NSArray arrayWithObject:NSPasteboardTypeString]];
}

- (IBAction)bt_analyse:(id)sender {
	if ([ch_rec state] == NSOnState) {
		
		const char *arg = [[tx_files stringValue] UTF8String];
		//rec(0,arg);
	}
}

- (IBAction)bt_load_ftp:(id)sender {
}

- (IBAction)bt_path:(id)sender {
}
@end
