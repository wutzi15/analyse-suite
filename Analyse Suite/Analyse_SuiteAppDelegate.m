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
#import "move_files.h"

@implementation Analyse_SuiteAppDelegate

@synthesize ch_rec;
@synthesize ch_plot;

@synthesize ch_wl;
@synthesize ch_peak;
@synthesize tx_ftp;
@synthesize tx_dir;
@synthesize tx_files;
@synthesize spin;
@synthesize ch_copy;
@synthesize tx_download;

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
			
			NSTask *task = [[NSTask alloc] init];
			[task setLaunchPath:@"/bin/sh"];
			[task setArguments:[NSArray arrayWithObjects:[[NSBundle mainBundle] pathForResource:@"dist" ofType:@"sh"], nil]];
			[task launch];
			
			int ret = collect_peak(arg);
			if (ret != 0) {
				NSLog(@"error in peak");
			}
		}
		
		
		if ([ch_plot state] ==NSOnState) {
			NSTask *task = [[NSTask alloc] init];
			[task setLaunchPath:@"/bin/sh"];
			[task setArguments:[NSArray arrayWithObjects:[[NSBundle mainBundle] pathForResource:@"plot" ofType:@"sh"], nil]];
			[task launch];
		}
	if (!([[tx_dir stringValue] isEqualToString:@""] ) && [ch_copy state] == NSOnState) {
		move_files([[tx_dir stringValue] UTF8String], [[tx_files stringValue] UTF8String]);
	}
		
		[spin stopAnimation:self];
	//}
}

- (IBAction)bt_load_ftp:(id)sender {
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/bin/sh"];
	[task setArguments:[NSArray arrayWithObjects:[[NSBundle mainBundle] pathForResource:@"ftp" ofType:@"sh"],[tx_download stringValue],[tx_ftp stringValue], nil]];
	[task launch];
}

- (IBAction)bt_path:(id)sender {
	long int result;
    NSArray *fileTypes = [NSArray arrayWithObject:@""];
    NSOpenPanel *oPanel = [NSOpenPanel openPanel];
	
    [oPanel setAllowsMultipleSelection:NO];
	[oPanel setCanCreateDirectories:YES];
	[oPanel setCanChooseDirectories:YES];
	[oPanel setCanChooseFiles:NO];
    result = [oPanel runModalForDirectory:NSHomeDirectory()
									 file:nil types:fileTypes];
    if (result == NSOKButton) {
        NSArray *filesToOpen = [oPanel filenames];
        unsigned long int count = [filesToOpen count];
        for (int i=0; i<count; i++) {
            [tx_dir setStringValue:[filesToOpen objectAtIndex:i]];
            //id currentDoc = [[ToDoDoc alloc] initWithFile:aFile];
        }
    }
	
}
@end
