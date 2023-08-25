import { ComponentFixture, TestBed } from '@angular/core/testing';
import { SwitchTabPage } from './switch-tab.page';

describe('SwitchTabPage', () => {
  let component: SwitchTabPage;
  let fixture: ComponentFixture<SwitchTabPage>;

  beforeEach(async(() => {
    fixture = TestBed.createComponent(SwitchTabPage);
    component = fixture.componentInstance;
    fixture.detectChanges();
  }));

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
