/*** Copyright (c), The Regents of the University of California            ***
 *** For more information please refer to files in the COPYRIGHT directory ***/
/* phyBundleColl.h - This file may be generated by a program or 
 * script
 */

#ifndef PHY_BUNDLE_COLL_H
#define PHY_BUNDLE_COLL_H

/* This is a Object File I/O call */

#include "rods.h"
#include "rcMisc.h"
#include "procApiRequest.h"
#include "apiNumber.h"
#include "initServer.h"
#include "structFileExtAndReg.h"
#include "miscUtil.h"

#define BUNDLE_RESC	"bundleResc"
#define TAR_BUNDLE_TYPE	"tar bundle"
#define BUNDLE_STR     "bundle" // JMC - backport 4658
#define BUNDLE_RESC_CLASS	"bundle"

#define MAX_BUNDLE_SIZE		4	/* 4 G */
#define MAX_SUB_FILE_CNT	5120 // JMC - backport 4480

typedef struct BunReplCache {
    rodsLong_t  dataId;
    char objPath[MAX_NAME_LEN];         /* optional for IRODS_ADMIN_KW */
    char chksumStr[NAME_LEN]; // JMC - backport 4528
    int srcReplNum;
    struct BunReplCache *next;
} bunReplCache_t;

typedef struct BunReplCacheHeader {
    int numSubFiles;
    rodsLong_t totSubFileSize;
    bunReplCache_t *bunReplCacheHead;
} bunReplCacheHeader_t;

typedef struct CurSubFileCond {
    char collName[MAX_NAME_LEN];
    char dataName[MAX_NAME_LEN];
    rodsLong_t dataId;
    char subPhyPath[MAX_NAME_LEN];
    char cachePhyPath[MAX_NAME_LEN];
    int cacheReplNum;
    rodsLong_t subFileSize;
    int bundled;
} curSubFileCond_t;

#if defined(RODS_SERVER)
#define RS_PHY_BUNDLE_COLL rsPhyBundleColl
/* prototype for the server handler */
int
rsPhyBundleColl (rsComm_t *rsComm, 
structFileExtAndRegInp_t *phyBundleCollInp);
int
remotePhyBundleColl (rsComm_t *rsComm, 
structFileExtAndRegInp_t *phyBundleCollInp, rodsServerHost_t *rodsServerHost);
int
_rsPhyBundleColl (rsComm_t *rsComm, structFileExtAndRegInp_t *phyBundleCollInp,
rescGrpInfo_t *rescGrpInfo);
int
createPhyBundleDataObj (rsComm_t *rsComm, char *collection,
rescGrpInfo_t *rescGrpInfo, dataObjInp_t *dataObjInp, char *dataType); // JMC - backport 4658
int
createPhyBundleDir (rsComm_t *rsComm, char *bunFilePath,
char *outPhyBundleDir);
int
rsMkBundlePath (rsComm_t *rsComm, char *collection, char *outPath,  
int myRanNum);
int
replDataObjForBundle (rsComm_t *rsComm, char *collName, char *dataName,
char *rescName, char* rescHier, char* dstRescHier, int adminFlag, dataObjInfo_t *outCacheObjInfo);
int
isDataObjBundled (rsComm_t *rsComm, collEnt_t *collEnt);
int
setSubPhyPath (char *phyBunDir, rodsLong_t dataId, char *subBunPhyPath);
int
addSubFileToDir (curSubFileCond_t *curSubFileCond,
bunReplCacheHeader_t *bunReplCacheHeader);
int
replAndAddSubFileToDir (rsComm_t *rsComm, curSubFileCond_t *curSubFileCond,
char *myRescName, char *phyBunDir, bunReplCacheHeader_t *bunReplCacheHeader);
int
bundlleAndRegSubFiles (rsComm_t *rsComm, int l1descInx, char *phyBunDir, 
char *collection, bunReplCacheHeader_t *bunReplCacheHeader, int chksumFlag); // JMC - backport 4528
int
phyBundle (rsComm_t *rsComm, dataObjInfo_t *dataObjInfo, char *phyBunDir,
char *collection, int oprType); // JMC - backport 4643
#else
#define RS_PHY_BUNDLE_COLL NULL
#endif

/* prototype for the client call */
int
rcPhyBundleColl (rcComm_t *conn, 
structFileExtAndRegInp_t *phyBundleCollInp);

#endif	/* PHY_BUNDLE_COLL_H */
