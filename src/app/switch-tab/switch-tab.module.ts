import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';

import { IonicModule } from '@ionic/angular';

import { SwitchTabPageRoutingModule } from './switch-tab-routing.module';

import { SwitchTabPage } from './switch-tab.page';

@NgModule({
  imports: [
    CommonModule,
    FormsModule,
    IonicModule,
    SwitchTabPageRoutingModule
  ],
  declarations: [SwitchTabPage]
})
export class SwitchTabPageModule {}
