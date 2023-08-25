import { NgModule } from '@angular/core';
import { Routes, RouterModule } from '@angular/router';

import { SwitchTabPage } from './switch-tab.page';

const routes: Routes = [
  {
    path: '',
    component: SwitchTabPage
  }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule],
})
export class SwitchTabPageRoutingModule {}
