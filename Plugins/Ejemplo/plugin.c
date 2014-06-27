/* -----------------------------------------------------------------------
 * Paramics Programmer API    (paramics-support@quadstone.com)
 * Quadstone Ltd.             Tel: +44 131 220 4491
 * 16 Chester Street          Fax: +44 131 220 4492
 * Edinburgh, EH3 7RA, UK     WWW: http://www.paramics-online.com
 * ----------------------------------------------------------------------- */  

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "programmer.h"


void CollectorEntry(LINK* anterior, LINK* cinta, LINK* siguiente, int gap) {
	VEHICLE* prev; 
	VEHICLE* next;
	
		LINK* anteanterior;
		LINK* subsiguiente;
		float dist_prev, dist_next;
//Miramos hacia atras	
		prev = qpg_LNK_vehicleHead(anterior, 1);

		if (prev != NULL) {dist_prev = qpg_VHC_distance(prev); }
		else {
			anteanterior = qpg_LNK_entry(anterior, 1);
			prev = qpg_LNK_vehicleHead(anteanterior, 1);
				if (prev != NULL) { dist_prev = qpg_VHC_distance(prev) + qpg_LNK_length(anterior); }
				else {dist_prev = gap;}
		}
//Miramos hacia adelante

		next = qpg_LNK_vehicleTail(siguiente, 1);
	
		if (next != NULL) {
			dist_next = qpg_LNK_length(siguiente) - qpg_VHC_distance(next); 
		}
		else { 
			subsiguiente = qpg_LNK_exit(siguiente, 1);
			next = qpg_LNK_vehicleTail(subsiguiente, 1);
			if (next != NULL) {
				dist_next = qpg_LNK_length(siguiente)+qpg_LNK_length(subsiguiente) - qpg_VHC_distance(next); 
			}
			else {
				dist_next = gap; 
			}
		}
//Todo bien? pasamos!!
		if (dist_prev >= gap && dist_next >= gap) {
			qps_LNK_priority(cinta, siguiente, APIPRI_MINOR);
		}	
		else {
			qps_LNK_priority(cinta, siguiente, APIPRI_BARRED);
		}
	
}
int gap = 25;
void qpx_NET_timeStep() {
//T1	
CollectorEntry(qpg_NET_link("203:284"), qpg_NET_link("252:284"),qpg_NET_link("284:283"), gap);
CollectorEntry(qpg_NET_link("284:283"), qpg_NET_link("251:283"),qpg_NET_link("283:282"), gap);
CollectorEntry(qpg_NET_link("283:282"), qpg_NET_link("250:282"),qpg_NET_link("282:281"), gap);
CollectorEntry(qpg_NET_link("282:281"), qpg_NET_link("249:281"),qpg_NET_link("281:280"), gap);
CollectorEntry(qpg_NET_link("281:280"), qpg_NET_link("248:280"),qpg_NET_link("280:279"), gap);
CollectorEntry(qpg_NET_link("280:287"), qpg_NET_link("247:279"),qpg_NET_link("279:278"), gap);
CollectorEntry(qpg_NET_link("279:278"), qpg_NET_link("246:278"),qpg_NET_link("278:277"), gap);
CollectorEntry(qpg_NET_link("278:277"), qpg_NET_link("245:277"),qpg_NET_link("277:276"), gap);
CollectorEntry(qpg_NET_link("277:276"), qpg_NET_link("244:276"),qpg_NET_link("276:274"), gap);
CollectorEntry(qpg_NET_link("276:274"), qpg_NET_link("243:274"),qpg_NET_link("274:273"), gap);
CollectorEntry(qpg_NET_link("274:273"), qpg_NET_link("242:273"),qpg_NET_link("273:272"), gap);
CollectorEntry(qpg_NET_link("273:272"), qpg_NET_link("241:272"),qpg_NET_link("272:271"), gap);
CollectorEntry(qpg_NET_link("272:271"), qpg_NET_link("240:271"),qpg_NET_link("271:270"), gap);
CollectorEntry(qpg_NET_link("271:270"), qpg_NET_link("239:270"),qpg_NET_link("270:202"), gap);
CollectorEntry(qpg_NET_link("202:269"), qpg_NET_link("238:269"),qpg_NET_link("269:268"), gap);
CollectorEntry(qpg_NET_link("269:268"), qpg_NET_link("236:268"),qpg_NET_link("268:267"), gap);
CollectorEntry(qpg_NET_link("268:267"), qpg_NET_link("235:267"),qpg_NET_link("267:266"), gap);
CollectorEntry(qpg_NET_link("267:266"), qpg_NET_link("234:266"),qpg_NET_link("266:265"), gap);
CollectorEntry(qpg_NET_link("266:265"), qpg_NET_link("233:265"),qpg_NET_link("265:263"), gap);
CollectorEntry(qpg_NET_link("265:263"), qpg_NET_link("232:263"),qpg_NET_link("263:262"), gap);
CollectorEntry(qpg_NET_link("263:262"), qpg_NET_link("231:262"),qpg_NET_link("262:261"), gap);
CollectorEntry(qpg_NET_link("262:261"), qpg_NET_link("230:261"),qpg_NET_link("261:260"), gap);
CollectorEntry(qpg_NET_link("261:260"), qpg_NET_link("229:260"),qpg_NET_link("260:258"), gap);
CollectorEntry(qpg_NET_link("260:258"), qpg_NET_link("228:258"),qpg_NET_link("258:257"), gap);
CollectorEntry(qpg_NET_link("258:257"), qpg_NET_link("227:257"),qpg_NET_link("257:256"), gap);
CollectorEntry(qpg_NET_link("257:256"), qpg_NET_link("226:256"),qpg_NET_link("256:255"), gap);
CollectorEntry(qpg_NET_link("256:255"), qpg_NET_link("225:255"),qpg_NET_link("255:254"), gap);
CollectorEntry(qpg_NET_link("255:254"), qpg_NET_link("224:254"),qpg_NET_link("254:201"), gap);


CollectorEntry(qpg_NET_link("204:253"), qpg_NET_link("237:253"),qpg_NET_link("253:275"), gap);
CollectorEntry(qpg_NET_link("253:275"), qpg_NET_link("264:275"),qpg_NET_link("275:286"), gap);
CollectorEntry(qpg_NET_link("275:286"), qpg_NET_link("285:286"),qpg_NET_link("286:287"), gap);
CollectorEntry(qpg_NET_link("286:287"), qpg_NET_link("288:287"),qpg_NET_link("287:289"), gap);
CollectorEntry(qpg_NET_link("287:289"), qpg_NET_link("293:289"),qpg_NET_link("289:291"), gap);
CollectorEntry(qpg_NET_link("289:291"), qpg_NET_link("292:291"),qpg_NET_link("291:294"), gap);
CollectorEntry(qpg_NET_link("291:294"), qpg_NET_link("295:294"),qpg_NET_link("294:297"), gap);
CollectorEntry(qpg_NET_link("294:297"), qpg_NET_link("296:297"),qpg_NET_link("297:299"), gap);
CollectorEntry(qpg_NET_link("297:299"), qpg_NET_link("298:299"),qpg_NET_link("299:300"), gap);
CollectorEntry(qpg_NET_link("299:300"), qpg_NET_link("301:300"),qpg_NET_link("300:302"), gap);
CollectorEntry(qpg_NET_link("300:302"), qpg_NET_link("303:302"),qpg_NET_link("302:305"), gap);
CollectorEntry(qpg_NET_link("302:305"), qpg_NET_link("304:305"),qpg_NET_link("305:306"), gap);
CollectorEntry(qpg_NET_link("305:306"), qpg_NET_link("311:306"),qpg_NET_link("306:307"), gap);
CollectorEntry(qpg_NET_link("306:307"), qpg_NET_link("314:307"),qpg_NET_link("307:205"), gap);
CollectorEntry(qpg_NET_link("205:312"), qpg_NET_link("313:312"),qpg_NET_link("312:316"), gap);
CollectorEntry(qpg_NET_link("312:316"), qpg_NET_link("315:316"),qpg_NET_link("316:317"), gap);
CollectorEntry(qpg_NET_link("316:317"), qpg_NET_link("321:317"),qpg_NET_link("317:319"), gap);
CollectorEntry(qpg_NET_link("317:319"), qpg_NET_link("320:319"),qpg_NET_link("319:323"), gap);
CollectorEntry(qpg_NET_link("319:323"), qpg_NET_link("326:323"),qpg_NET_link("323:324"), gap);
CollectorEntry(qpg_NET_link("323:324"), qpg_NET_link("325:324"),qpg_NET_link("324:328"), gap);
CollectorEntry(qpg_NET_link("324:328"), qpg_NET_link("331:328"),qpg_NET_link("328:329"), gap);
CollectorEntry(qpg_NET_link("328:329"), qpg_NET_link("330:329"),qpg_NET_link("329:332"), gap);
CollectorEntry(qpg_NET_link("329:332"), qpg_NET_link("333:332"),qpg_NET_link("332:336"), gap);
CollectorEntry(qpg_NET_link("332:336"), qpg_NET_link("334:336"),qpg_NET_link("336:337"), gap);
CollectorEntry(qpg_NET_link("336:337"), qpg_NET_link("340:337"),qpg_NET_link("337:338"), gap);
CollectorEntry(qpg_NET_link("337:338"), qpg_NET_link("339:338"),qpg_NET_link("338:342"), gap);
CollectorEntry(qpg_NET_link("338:342"), qpg_NET_link("343:342"),qpg_NET_link("342:345"), gap);
CollectorEntry(qpg_NET_link("342:345"), qpg_NET_link("344:345"),qpg_NET_link("345:206"), gap);

CollectorEntry(qpg_NET_link("215:407"), qpg_NET_link("406:407"),qpg_NET_link("407:404"), gap);
CollectorEntry(qpg_NET_link("407:404"), qpg_NET_link("405:404"),qpg_NET_link("404:402"), gap);
CollectorEntry(qpg_NET_link("404:402"), qpg_NET_link("403:402"),qpg_NET_link("402:401"), gap);
CollectorEntry(qpg_NET_link("402:401"), qpg_NET_link("400:401"),qpg_NET_link("401:399"), gap);
CollectorEntry(qpg_NET_link("401:399"), qpg_NET_link("396:399"),qpg_NET_link("399:398"), gap);
CollectorEntry(qpg_NET_link("399:398"), qpg_NET_link("395:398"),qpg_NET_link("398:393"), gap);
CollectorEntry(qpg_NET_link("398:393"), qpg_NET_link("394:393"),qpg_NET_link("393:392"), gap);
CollectorEntry(qpg_NET_link("393:392"), qpg_NET_link("391:392"),qpg_NET_link("392:389"), gap);
CollectorEntry(qpg_NET_link("392:389"), qpg_NET_link("390:389"),qpg_NET_link("389:387"), gap);
CollectorEntry(qpg_NET_link("389:387"), qpg_NET_link("386:387"),qpg_NET_link("387:385"), gap);
CollectorEntry(qpg_NET_link("387:385"), qpg_NET_link("384:385"),qpg_NET_link("385:381"), gap);
CollectorEntry(qpg_NET_link("385:381"), qpg_NET_link("383:381"),qpg_NET_link("381:378"), gap);
CollectorEntry(qpg_NET_link("381:378"), qpg_NET_link("377:378"),qpg_NET_link("378:380"), gap);
CollectorEntry(qpg_NET_link("378:380"), qpg_NET_link("375:380"),qpg_NET_link("380:214"), gap);
CollectorEntry(qpg_NET_link("214:372"), qpg_NET_link("376:372"),qpg_NET_link("372:371"), gap);
CollectorEntry(qpg_NET_link("372:371"), qpg_NET_link("374:371"),qpg_NET_link("371:370"), gap);
CollectorEntry(qpg_NET_link("371:370"), qpg_NET_link("369:370"),qpg_NET_link("370:367"), gap);
CollectorEntry(qpg_NET_link("370:367"), qpg_NET_link("368:367"),qpg_NET_link("367:365"), gap);
CollectorEntry(qpg_NET_link("367:365"), qpg_NET_link("364:365"),qpg_NET_link("365:366"), gap);
CollectorEntry(qpg_NET_link("365:366"), qpg_NET_link("363:366"),qpg_NET_link("366:361"), gap);
CollectorEntry(qpg_NET_link("366:361"), qpg_NET_link("362:361"),qpg_NET_link("361:360"), gap);
CollectorEntry(qpg_NET_link("361:360"), qpg_NET_link("358:360"),qpg_NET_link("360:356"), gap);
CollectorEntry(qpg_NET_link("360:356"), qpg_NET_link("357:356"),qpg_NET_link("356:355"), gap);
CollectorEntry(qpg_NET_link("356:355"), qpg_NET_link("354:355"),qpg_NET_link("355:352"), gap);
CollectorEntry(qpg_NET_link("355:352"), qpg_NET_link("351:352"),qpg_NET_link("352:353"), gap);
CollectorEntry(qpg_NET_link("352:353"), qpg_NET_link("350:353"),qpg_NET_link("353:349"), gap);
CollectorEntry(qpg_NET_link("353:349"), qpg_NET_link("348:349"),qpg_NET_link("349:346"), gap);
CollectorEntry(qpg_NET_link("349:346"), qpg_NET_link("347:346"),qpg_NET_link("346:213"), gap);


CollectorEntry(qpg_NET_link("216:408"), qpg_NET_link("409:408"),qpg_NET_link("408:411"), gap);
CollectorEntry(qpg_NET_link("408:411"), qpg_NET_link("410:411"),qpg_NET_link("411:412"), gap);
CollectorEntry(qpg_NET_link("411:412"), qpg_NET_link("413:412"),qpg_NET_link("412:415"), gap);
CollectorEntry(qpg_NET_link("412:415"), qpg_NET_link("416:415"),qpg_NET_link("415:418"), gap);
CollectorEntry(qpg_NET_link("415:418"), qpg_NET_link("417:418"),qpg_NET_link("418:419"), gap);
CollectorEntry(qpg_NET_link("418:419"), qpg_NET_link("421:419"),qpg_NET_link("419:423"), gap);
CollectorEntry(qpg_NET_link("419:423"), qpg_NET_link("422:423"),qpg_NET_link("423:424"), gap);
CollectorEntry(qpg_NET_link("423:424"), qpg_NET_link("425:424"),qpg_NET_link("424:430"), gap);
CollectorEntry(qpg_NET_link("424:430"), qpg_NET_link("426:430"),qpg_NET_link("430:431"), gap);
CollectorEntry(qpg_NET_link("430:431"), qpg_NET_link("427:431"),qpg_NET_link("431:432"), gap);
CollectorEntry(qpg_NET_link("431:432"), qpg_NET_link("437:432"),qpg_NET_link("432:433"), gap);
CollectorEntry(qpg_NET_link("432:433"), qpg_NET_link("434:433"),qpg_NET_link("433:442"), gap);
CollectorEntry(qpg_NET_link("433:442"), qpg_NET_link("438:442"),qpg_NET_link("442:440"), gap);
CollectorEntry(qpg_NET_link("442:440"), qpg_NET_link("439:440"),qpg_NET_link("440:443"), gap);
CollectorEntry(qpg_NET_link("440:443"), qpg_NET_link("446:443"),qpg_NET_link("443:444"), gap);
CollectorEntry(qpg_NET_link("443:444"), qpg_NET_link("445:444"),qpg_NET_link("444:449"), gap);
CollectorEntry(qpg_NET_link("444:449"), qpg_NET_link("447:449"),qpg_NET_link("449:450"), gap);
CollectorEntry(qpg_NET_link("449:450"), qpg_NET_link("448:450"),qpg_NET_link("450:454"), gap);
CollectorEntry(qpg_NET_link("450:454"), qpg_NET_link("452:454"),qpg_NET_link("454:455"), gap);
CollectorEntry(qpg_NET_link("454:455"), qpg_NET_link("453:455"),qpg_NET_link("455:217"), gap);

CollectorEntry(qpg_NET_link("26:27"), qpg_NET_link("154:27"),qpg_NET_link("27:28"), gap);
CollectorEntry(qpg_NET_link("27:28"), qpg_NET_link("168:28"),qpg_NET_link("28:29"), gap);
CollectorEntry(qpg_NET_link("37:38"), qpg_NET_link("178:38"),qpg_NET_link("38:39"), gap);
CollectorEntry(qpg_NET_link("38:39"), qpg_NET_link("181:39"),qpg_NET_link("39:40"), gap);

}
