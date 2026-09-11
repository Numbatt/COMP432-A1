
#ifndef BUFFER_MGR_H
#define BUFFER_MGR_H

#include "MyDB_PageHandle.h"
#include "MyDB_Table.h"

using namespace std;

class MyDB_BufferManager {

public:

	// THESE METHODS MUST APPEAR AND THE PROTOTYPES CANNOT CHANGE!

	// gets the i^th page in the table whichTable... note that if the page
	// is currently being used (that is, the page is current buffered) a handle
	// to that already-buffered page should be returned.
	//
	// note that a table is identified by its storage location; two different
	// MyDB_Table objects having the same storage location refer to the same
	// table, and so getPage on the i^th page of either one gives you the very
	// same page
	MyDB_PageHandle getPage (MyDB_TablePtr whichTable, long i);

	// gets a temporary page that will no longer exist (1) after the buffer manager
	// has been destroyed, or (2) there are no more references to it anywhere in the
	// program.  Typically such a temporary page will be used as buffer memory.
	// since it is just a temp page, it is not associated with any particular
	// table
	MyDB_PageHandle getPage ();

	// gets the i^th page in the table whichTable... the only difference
	// between this method and getPage (whichTable, i) is that the page will be
	// pinned in RAM; it cannot be evicted from the buffer pool.
	//
	// if every page in the pool is already pinned, so that there is no room to
	// pin another one, this returns a nullptr.
	//
	// note that pinning is a property of the page, and not of the handle.  Once
	// a page is pinned it stays pinned until it is unpinned, so asking for the
	// same page later via getPage () does NOT unpin it
	MyDB_PageHandle getPinnedPage (MyDB_TablePtr whichTable, long i);

	// gets a temporary page, like getPage (), except that this one is pinned.
	// as above, returns a nullptr if there is no room to pin another page
	MyDB_PageHandle getPinnedPage ();

	// un-pins the page that the specified handle refers to.  Since pinning is a
	// property of the page, this unpins the page for everyone, even if other
	// handles to that same page are still out there
	void unpin (MyDB_PageHandle unpinMe);

	// creates an LRU buffer manager... params are as follows:
	// 1) the size of each page is pageSize
	// 2) the number of pages managed by the buffer manager is numPages;
	// 3) temporary pages are written to the file tempFile
	MyDB_BufferManager (size_t pageSize, size_t numPages, string tempFile);

	// when the buffer manager is destroyed, all of the dirty pages need to be
	// written back to disk (including any that are still pinned), and any
	// temporary files need to be deleted
	~MyDB_BufferManager ();

	// a buffer manager owns its pool of memory and its open files, so copying
	// one would leave two managers trying to free the same resources.  Copying
	// is not allowed
	MyDB_BufferManager (const MyDB_BufferManager &) = delete;
	MyDB_BufferManager &operator = (const MyDB_BufferManager &) = delete;

	// FEEL FREE TO ADD ADDITIONAL PUBLIC METHODS

private:

	// YOUR STUFF HERE

};

#endif

