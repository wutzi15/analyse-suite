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
	NSButton *ch_rec;
	NSButton *ch_plot;
	NSButton *ch_wl;
	NSButton *ch_peak;
	NSTextField *tx_ftp;
	NSTextField *tx_dir;
	NSTextField *tx_files;
	NSProgressIndicator *spin;
	NSButton *ch_copy;
	NSTextField *tx_download;
}
@property (assign) IBOutlet NSButton *ch_rec;
@property (assign) IBOutlet NSButton *ch_plot;

@property (assign) IBOutlet NSButton *ch_wl;
@property (assign) IBOutlet NSButton *ch_peak;
@property (assign) IBOutlet NSTextField *tx_ftp;
@property (assign) IBOutlet NSTextField *tx_dir;
@property (assign) IBOutlet NSTextField *tx_files;
@property (assign) IBOutlet NSProgressIndicator *spin;
@property (assign) IBOutlet NSButton *ch_copy;
@property (assign) IBOutlet NSTextField *tx_download;


@property (assign) IBOutlet NSWindow *window;
- (IBAction)bt_analyse:(id)sender;
- (IBAction)bt_load_ftp:(id)sender;
- (IBAction)bt_path:(id)sender;
- (IBAction)clear_input_files:(id)sender;
- (IBAction)clear_all:(id)sender;

@end
