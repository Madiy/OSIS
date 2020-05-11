#include <stdio.h>
#include <stdlib.h>
#include <hdd/api.h>
#include <fat32/api.h>
#include <test/api.h>
#include <locale.h>

char Max_Size_File_Name[10000];
UINT32 Max_Size=0;

typedef struct {
  FAT32_CB_T * cb;
  HANDLE handle;
} WSFPARMS;

typedef struct {
  FAT32_CB_T * cb;
  ISPROC * isproc;
} READ_CLUSTER_PARMS;

typedef struct {
  FAT32_DIR_ENTRY_T * entry;
  bool result;                  
} SEARCH_ENTRY;

bool read_cluster_MAX(void * iclusters, UINT cluster) {
  READ_CLUSTER_PARMS * parms =
    (READ_CLUSTER_PARMS*)(((ICLUSTERS *)iclusters)->ptr);

  if(cluster >= FAT32_BAD)
    return true;

  UINT32 sector = fat32_get_sector_by_cluster(parms->cb, cluster);
  return !fat32_read_sectors(parms->cb, sector,
      parms->cb->bootSector.bpb.BPB_SecPerClus, parms->isproc);
}
bool fat32_print_dir_entry_MAX(FAT32_DIR_ENTRY_T * entry) {
  int i;
  char * c = entry->DIR_Name;
  if (*c == 0)
    return false;
	if(entry->DIR_Attr==32)
	{
	  printf("\nDIR_Name=");
	  for(i=0; i<sizeof(entry->DIR_Name); i++,c++) putchar(*c);
	  printf("\nDIR_Attr=%02x\n", entry->DIR_Attr);
	  printf("DIR_NTRes=%02x\n", entry->DIR_NTRes);
	  printf("DIR_CrtTime_Tenth=%02x\n", entry->DIR_CrtTime_Tenth);
	  printf("DIR_CrtTime=%04x\n", entry->DIR_CrtTime);
	  printf("DIR_CrtDate=%04x\n", entry->DIR_CrtDate);
	  printf("DIR_LstAccDate=%04x\n", entry->DIR_LstAccDate);
	  printf("DIR_FstClusHI=%04x\n", entry->DIR_FstClusHI);
	  printf("DIR_WrtTime=%04x\n", entry->DIR_WrtTime);
	  printf("DIR_WrtDate=%04x\n", entry->DIR_WrtDate);
	  printf("DIR_FstClusLO=%04x\n", entry->DIR_FstClusLO);
	  printf("DIR_FileSize=%08x\n", entry->DIR_FileSize);
	  
	  if(entry->DIR_FileSize > Max_Size)
	  {
	  		char * c = entry->DIR_Name;
	  		if(c[0]!=-27){
			  
			  	for(i=0; i<sizeof(entry->DIR_Name); i++,c++) 
			  	{
			  
			  		Max_Size_File_Name[i] = *c;
			  	}
			  	Max_Size_File_Name[i+1]='\0';
			  	Max_Size = entry->DIR_FileSize;
		  };
	  };
  }
  return true;
}

bool fat32_get_cluster_chain_MAX(FAT32_CB_T * cb,
  UINT32 cluster, ICLUSTERS * proc) {
  bool result = true;
  UINT32 current_sector = 0;
  UINT8 * buf = (UINT8 *)alloca(cb->bootSector.bpb.BPB_BytsPerSec);
  UINT32 entry_sector;
  UINT16 entry_offset;

  while(result && !proc->proc(proc, cluster)) 
  {
    fat32_get_fat_entry_by_cluster(cb,
      &entry_sector, &entry_offset,cluster);

    if (current_sector != entry_sector) {
      result = fat32_read_sector(cb, buf, entry_sector);
      current_sector = entry_sector;
    }
    if (result) {
      cluster = *((UINT32 *)((UINT8 *)(buf+entry_offset))) & FAT32_MASK;
    }
  }
  return result;
}

bool fat32_read_cluster_chain_MAX(FAT32_CB_T * cb,
  UINT32 cluster, ISPROC * proc) {

  READ_CLUSTER_PARMS read_cluster_parms;
  read_cluster_parms.cb = cb;
  read_cluster_parms.isproc = proc;

  ICLUSTERS ifc;
  ifc.proc = read_cluster_MAX;
  ifc.ptr = &read_cluster_parms;

  return fat32_get_cluster_chain_MAX(cb, cluster, &ifc);
}

bool search_file_MAX(void * ifc, void * buf, UINT32 bufsz) {
  ISPROC * iface = (ISPROC *)ifc;
  SEARCH_ENTRY * search_entry = (SEARCH_ENTRY *)iface->ptr;
  FAT32_DIR_ENTRY_T * entry = search_entry->entry;
  FAT32_DIR_ENTRY_T * dirEntry = (FAT32_DIR_ENTRY_T *)buf;
  bool result = false;
  UINT32 i;

  for(i=0; i<bufsz/sizeof(FAT32_DIR_ENTRY_T);
        i++,dirEntry++ ) {
    fat32_print_dir_entry_MAX(dirEntry);
    result = !memcmp(dirEntry->DIR_Name,
      entry->DIR_Name, sizeof(dirEntry->DIR_Name));
    if (result) {
      memcpy(entry, dirEntry, sizeof(FAT32_DIR_ENTRY_T));
      search_entry->result = result;
      break;
    }
  }
  return result;

}

bool fat32_search_MAX_dir(FAT32_CB_T * cb,
    FAT32_DIR_ENTRY_T * entry) {

  SEARCH_ENTRY search_entry;
  search_entry.entry = entry;
  search_entry.result = false;

  ISPROC ifc;
  ifc.ptr = &search_entry;
  ifc.proc = search_file_MAX;

  fat32_read_cluster_chain_MAX(cb, cb->bootSector.bpb.BPB_RootClus, &ifc );

  return search_entry.result;	
}

void getMaxSized()
{
  HDD_CB_T hdd_cb;
  FAT32_CB_T cb;
  FAT32_DIR_ENTRY_T entry;
  UINT8 id=1;
  bool result = hdd_open_device(&hdd_cb, id);
  printf( result ?
    "Sector finded %x\n" : "Sector not finded" , hdd_cb.lbaStart );

  result = result && fat32_open_device(&cb, &hdd_cb);
  if (result) {
    fat32_print_control_block(&cb);

    memset(&entry, 0, sizeof(entry));
    memcpy(entry.DIR_Name, "KERNEL     ", sizeof(entry.DIR_Name));

    result = fat32_search_MAX_dir(&cb, &entry); //2

  }
}

int main(int argc, char *argv[])
{
	int i=0;
  setlocale(LC_ALL, "Rus");
  getMaxSized();
  printf("Max size = %d\n",Max_Size);
  printf("Name = %s",Max_Size_File_Name);
  return 0;
}

