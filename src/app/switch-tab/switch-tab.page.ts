import { Component, OnInit } from '@angular/core';
import { HttpClient, HttpHeaders, HttpParams, HttpResponse } from '@angular/common/http';

@Component({
  selector: 'app-switch-tab',
  templateUrl: './switch-tab.page.html',
  styleUrls: ['./switch-tab.page.scss'],
})
export class SwitchTabPage implements OnInit {
  data: any;
  fanRelayChecked : boolean = false;

  constructor(private http: HttpClient) {}

  ngOnInit() {
    this.doGetRelayStatus();
  }

  doGetRelayStatus() {
    
    let queryParams = new HttpParams();
    queryParams = queryParams.append("device_id","control_01");
    queryParams = queryParams.append("relay_type","fan");

    let options = {
      observe: 'response' as 'response',
      queryParams: queryParams
    };
    
    this.http.get<any>('https://nhmkbym3v5tf7jzhqcqdq32vry0tidfc.lambda-url.us-east-2.on.aws?device_id=control_01&relay_type=fan', options).subscribe(res => {
      let response: HttpResponse<any> = res;
      this.data = res.body; // 這裡一樣會對 JSON 進行自動反序列化
      if (1 == this.data.switch) {
        this.fanRelayChecked = true;
      }
    });

  }

  onChange(switchType:string) {
    console.log("[TEST] " + switchType + "::" + this.fanRelayChecked);
    switch(switchType) {
      case "fan":
        this.doSwitchFanRelay();
        break;
      default:

    }
  }

  doSwitchFanRelay() {
    var changeTo = (this.fanRelayChecked) ? 0 : 1;
    let body = {
      "device_id":"control_01",
      "relay_type":"fan",
      "switch":changeTo
    }

    this.http.post<any>('https://aw2i363uamd4u4l2rt4mq5pqpe0lapuj.lambda-url.us-east-2.on.aws', body).subscribe(data => {
      let response: HttpResponse<any> = data;
      this.data = data.body;  
      console.log(data)
    });
  }
}
