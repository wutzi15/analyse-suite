//
//  Analyse_SuiteAppDelegate.m
//  Analyse Suite
//
//  Created by Wutzi on 14.03.11.
//  Copyright 2011 me. All rights reserved.
//

#import "Analyse_SuiteAppDelegate.h"
#import "rec.h"
#import "head_analyse.h"
#import "collect_peak.h"


@implementation Analyse_SuiteAppDelegate

@synthesize ch_rec;
@synthesize ch_plot;

@synthesize ch_wl;
@synthesize ch_peak;
@synthesize tx_ftp;
@synthesize tx_dir;
@synthesize tx_files;
@synthesize spin;

@synthesize window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
	[tx_files setEnabled:YES];
	[tx_files setEditable:YES];
	[tx_files setStringValue:@""];
	[tx_files registerForDraggedTypes:[NSArray arrayWithObject:NSFilenamesPboardType]];
	[tx_dir registerForDraggedTypes:[NSArray arrayWithObject:NSFilenamesPboardType]];
}

- (IBAction)bt_analyse:(id)sender {
	[spin startAnimation:self];
	const char *arg = [[tx_files stringValue] UTF8String];
	if ([ch_rec state] == NSOnState) {
		
		
		int ret = rec(arg);
		if (ret != 0) {
			NSLog(@"error in rec");
		}
	}
	if ([ch_wl state] == NSOnState) {
		int ret = _analyse(arg);
		if (ret != 0){
			NSLog(@"error in ana");
		}
	}
	if ([ch_peak state]){
		int ret = collect_peak(arg);
		if (ret != 0) {
			NSLog(@"error in peak");
		}
	}
	[spin stopAnimation:self];
}

- (IBAction)bt_load_ftp:(id)sender {
}

- (IBAction)bt_path:(id)sender {
}
@end
