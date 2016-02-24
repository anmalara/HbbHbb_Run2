float nL1Pt1PtPt3Pt4(float x){
	return ((0.5+(0.5*TMath::Erf((((x-37.7622)*(((x-37.7622)>219.612)/131.734))+((x-37.7622)*(((x-37.7622)<219.612)/43.5059)))+(219.612*(((1/131.734)-(1/43.5059))*((x-37.7622)<219.612))))))*0.90796)+0.0927401 ; }

float nCaloPt4(float x){
	return ((0.5+(0.5*TMath::Erf((((x+39758.7)*(((x+39758.7)>39839.3)/19146.7))+((x+39758.7)*(((x+39758.7)<39839.3)/14.1307)))+(39839.3*(((1/19146.7)-(1/14.1307))*((x+39758.7)<39839.3))))))*0.931116)+0.0492347 ; }

float nCaloCSV3(float x){
	return ((0.5+(0.5*TMath::Erf((((x+0.447175)*(((x+0.447175)>1.67748)/2.65565))+((x+0.447175)*(((x+0.447175)<1.67748)/13.1007)))+(1.67748*(((1/2.65565)-(1/13.1007))*((x+0.447175)<1.67748))))))*3.54556)-2.76519 ; }

float nPFPt4(float x){
	return ((0.5+(0.5*TMath::Erf((((x+39760)*(((x+39760)>39838)/11644.2))+((x+39760)*(((x+39760)<39838)/9.08955)))+(39838*(((1/11644.2)-(1/9.08955))*((x+39760)<39838))))))*0.238266)+0.74733 ; }

float nL1Pt1PtPt3Pt4Up(float x){
	return ((0.5+(0.5*TMath::Erf((((x-37.7622)*(((x-37.7622)>219.612)/131.734))+((x-37.7622)*(((x-37.7622)<219.612)/43.5059)))+(219.612*(((1/131.734)-(1/43.5059))*((x-37.7622)<219.612))))))*0.90796)+0.0927401 ; }

float nCaloPt4Up(float x){
	return ((0.5+(0.5*TMath::Erf((((x+39758.7)*(((x+39758.7)>39839.3)/19146.7))+((x+39758.7)*(((x+39758.7)<39839.3)/14.1307)))+(39839.3*(((1/19146.7)-(1/14.1307))*((x+39758.7)<39839.3))))))*0.934992)+0.0492347 ; }

float nCaloCSV3Up(float x){
	return ((0.5+(0.5*TMath::Erf((((x+0.447175)*(((x+0.447175)>1.67748)/2.65565))+((x+0.447175)*(((x+0.447175)<1.67748)/13.1007)))+(1.67748*(((1/2.65565)-(1/13.1007))*((x+0.447175)<1.67748))))))*3.60506)-2.76519 ; }

float nPFPt4Up(float x){
	return ((0.5+(0.5*TMath::Erf((((x+39760)*(((x+39760)>39838)/11644.2))+((x+39760)*(((x+39760)<39838)/9.08955)))+(39838*(((1/11644.2)-(1/9.08955))*((x+39760)<39838))))))*0.294553)+0.74733 ; }

float nL1Pt1PtPt3Pt4Down(float x){
	return ((0.5+(0.5*TMath::Erf((((x-37.7622)*(((x-37.7622)>219.612)/131.734))+((x-37.7622)*(((x-37.7622)<219.612)/43.5059)))+(219.612*(((1/131.734)-(1/43.5059))*((x-37.7622)<219.612))))))*0.90796)+0.0927401 ; }

float nCaloPt4Down(float x){
	return ((0.5+(0.5*TMath::Erf((((x+39758.7)*(((x+39758.7)>39839.3)/19146.7))+((x+39758.7)*(((x+39758.7)<39839.3)/14.1307)))+(39839.3*(((1/19146.7)-(1/14.1307))*((x+39758.7)<39839.3))))))*0.92724)+0.0492347 ; }

float nCaloCSV3Down(float x){
	return ((0.5+(0.5*TMath::Erf((((x+0.447175)*(((x+0.447175)>1.67748)/2.65565))+((x+0.447175)*(((x+0.447175)<1.67748)/13.1007)))+(1.67748*(((1/2.65565)-(1/13.1007))*((x+0.447175)<1.67748))))))*3.48606)-2.76519 ; }

float nPFPt4Down(float x){
	return ((0.5+(0.5*TMath::Erf((((x+39760)*(((x+39760)>39838)/11644.2))+((x+39760)*(((x+39760)<39838)/9.08955)))+(39838*(((1/11644.2)-(1/9.08955))*((x+39760)<39838))))))*0.181978)+0.74733 ; }

float QuadTriggerWeight(float pt1, float pt2, float pt3, float pt4 , float CSV3){
	if(isnan(CSV3)) CSV3=0;
	CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return nL1Pt1PtPt3Pt4(pt1+pt2+pt3+pt4)*nCaloPt4(pt4)*nPFPt4(pt4)*nCaloCSV3(-log(1-CSV3+1.e-7)) ; }

float QuadTriggerWeightUp(float pt1, float pt2, float pt3, float pt4 , float CSV3){
	if(isnan(CSV3)) CSV3=0;
	CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return nL1Pt1PtPt3Pt4Up(pt1+pt2+pt3+pt4)*nCaloPt4Up(pt4)*nPFPt4Up(pt4)*nCaloCSV3Up(-log(1-CSV3+1.e-7)) ; }

float QuadTriggerWeightDown(float pt1, float pt2, float pt3, float pt4 , float CSV3){
	if(isnan(CSV3)) CSV3=0;
	CSV3=CSV3>1?1:CSV3;CSV3=CSV3<0?0:CSV3;
	return nL1Pt1PtPt3Pt4Down(pt1+pt2+pt3+pt4)*nCaloPt4Down(pt4)*nPFPt4Down(pt4)*nCaloCSV3Down(-log(1-CSV3+1.e-7)) ; }

