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
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[tx_dir setStringValue:[defaults stringForKey:@"dir"]];
	[tx_download setStringValue:[defaults stringForKey:@"download"]];
	[tx_files setStringValue:[defaults stringForKey:@"files"]];
	[tx_ftp setStringValue:[defaults stringForKey:@"ftp"]];
	
	[ch_copy setState:[defaults integerForKey:@"copy"]];
	[ch_peak setState:[defaults integerForKey:@"peak"]];
	[ch_plot setState:[defaults integerForKey:@"plot"]];
	[ch_rec	setState:[defaults integerForKey:@"rec"]];
	[ch_wl setState:[defaults integerForKey:@"wl"]];
	
	
}
-(void)applicationWillTerminate:(NSNotification *)notification{
	NSUserDefaults *defaults = [NSUserDefaults standardUserDefaults];
	[defaults setValue:[tx_dir stringValue] forKey:@"dir"];
	[defaults setValue:[tx_download stringValue] forKey:@"download"];
	[defaults setValue:[tx_files stringValue] forKey:@"files"];
	[defaults setValue:[tx_ftp stringValue] forKey:@"ftp"];
	
	[defaults setInteger:[ch_copy state] forKey:@"copy"];
	[defaults setInteger:[ch_peak state] forKey:@"peak"];
	[defaults setInteger:[ch_plot state] forKey:@"plot"];
	[defaults setInteger:[ch_rec state] forKey:@"rec"];
	[defaults setInteger:[ch_wl state] forKey:@"wl"];
}

- (IBAction)bt_analyse:(id)sender {
	
	
	[spin startAnimation:self];
	if ([ch_plot state] == NSOnState) {
		[ch_copy setState:NSOnState];
	}
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
		
		int ret = collect_peak(arg,[[tx_dir stringValue]UTF8String]);
		if (ret != 0) {
			NSLog(@"error in peak");
		}
	}
	if (!([[tx_dir stringValue] isEqualToString:@""] ) && [ch_copy state] == NSOnState) {
		copy_files([[tx_dir stringValue] UTF8String], [[tx_files stringValue] UTF8String]);
	}
	
	NSFileManager *filemgr;
	NSString *currentpath;
	
	filemgr = [NSFileManager defaultManager];
	
	currentpath = [filemgr currentDirectoryPath];
	
	NSLog (@"Current directory is %@", currentpath);
	
	if ([filemgr changeCurrentDirectoryPath: [tx_dir stringValue]] == NO)
        NSLog (@"Cannot change directory.");
	
	currentpath = [filemgr currentDirectoryPath];
	
	NSLog (@"Current directory is %@", currentpath);
	
	if ([ch_plot state] ==NSOnState) {
		NSTask *task = [[NSTask alloc] init];
		[task setLaunchPath:@"/bin/sh"];
		[task setArguments:[NSArray arrayWithObjects:[[NSBundle mainBundle] pathForResource:@"plot" ofType:@"sh"], nil]];
		[task launch];
	}
	
	
	[spin stopAnimation:self];
	//}
}

- (IBAction)bt_load_ftp:(id)sender {
	[spin startAnimation:self];
	NSTask *task = [[NSTask alloc] init];
	[task setLaunchPath:@"/bin/sh"];
	[task setArguments:[NSArray arrayWithObjects:[[NSBundle mainBundle] pathForResource:@"ftp" ofType:@"sh"],[tx_download stringValue],[tx_ftp stringValue], nil]];
	[task launch];
	[spin stopAnimation:self];
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
