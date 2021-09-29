const Unit = {
    TiB: 40,
    GiB: 30,
    MiB: 20,
    KiB: 10
};

let virtualAddress;
let physicalAddress;

let virtualAddressSpaceTextbox, virtualAddressSpaceSelect;
let physicalAddressSpaceTextbox, physicalAddressSpaceSelect;
let pageSizeTextbox, pageSizeSelect;
let pageTableSizeTextbox, pageTableSizeSelect;
let TLBMappingSelect;
let entriesTextbox;

let virtualAddressTagSizeText;
let virtualAddressIndexSizeText;
let virtualAddressPageSizeText;

let physicalAddressTagSizeText;
let physicalAddressPageSizeText;

let pageTableSizeText;

function setup(){
    createCanvas(1200, 500);
    background(0);
    fill(255)
        .strokeWeight(0)
        .textSize(20);

    /// DATA INPUT
    virtualAddressSpaceTextbox = select("#virtualAddressSpaceTextbox");
    virtualAddressSpaceSelect = select("#virtualAddressSpaceSelect");
    physicalAddressSpaceTextbox = select("#physicalAddressSpaceTextbox");
    physicalAddressSpaceSelect = select("#physicalAddressSpaceSelect");
    pageSizeTextbox = select("#pageSizeTextbox");
    pageSizeSelect = select("#pageSizeSelect");
    pageTableSizeTextbox = select("#pageTableSizeTextbox");
    pageTableSizeSelect = select("#pageTableSizeSelect");
    TLBMappingSelect = select("#TLBMappingSelect");
    entriesTextbox = select("#entriesTextbox");

    
    setInputFilter(document.getElementById("virtualAddressSpaceTextbox"), numFilter);
    setInputFilter(document.getElementById("physicalAddressSpaceTextbox"), numFilter);
    setInputFilter(document.getElementById("pageSizeTextbox"), numFilter);
    setInputFilter(document.getElementById("pageTableSizeTextbox"), numFilter);
    setInputFilter(document.getElementById("entriesTextbox"), numFilter);

    /// VIRTUAL ADDRESS OUTPUT
    virtualAddressTagSizeText = select("#virtualAddressTagSizeText");
    virtualAddressIndexSizeText = select("#virtualAddressIndexSizeText");
    virtualAddressPageSizeText = select("#virtualAddressPageSizeText");

    /// PHYSICAL ADDRESS OUTPUT
    physicalAddressTagSizeText = select("#physicalAddressTagSizeText");
    physicalAddressPageSizeText = select("#physicalAddressPageSizeText");

    // PAGE TABLE SIZE OUTPUT
    pageTableSizeText = select("#pageTableSizeText");
}

function updateVirtualAddress(){
    let index = Math.log2(entriesTextbox.value() / TLBMappingSelect.value());
    let pageOffset = Math.log2(pageSizeTextbox.value()) + Unit[pageSizeSelect.value()];
    let tag = Math.log2(virtualAddressSpaceTextbox.value()) + Unit[virtualAddressSpaceSelect.value()] - index - pageOffset;

    virtualAddress = new VirtualAddress(tag, index, pageOffset);
    virtualAddress.print();
}

function updatePhysicalAddress(){
    let pageOffset = Math.log2(pageSizeTextbox.value()) + Unit[pageSizeSelect.value()];
    let tag = Math.log2(physicalAddressSpaceTextbox.value()) + Unit[physicalAddressSpaceSelect.value()] - pageOffset;

    physicalAddress = new PhysicalAddress(tag, pageOffset);
    physicalAddress.print();
}

function updatePageTableSize(){
    let size = Math.log2(virtualAddressSpaceTextbox.value()) + Unit[virtualAddressSpaceSelect.value()];
    let pageOffset = Math.log2(pageSizeTextbox.value()) + Unit[pageSizeSelect.value()]; 

    let entries = size - pageOffset;
    let bytesPerEntry = Math.log2(pageTableSizeTextbox.value() / pageTableSizeSelect.value());

    let entryBytes = entries + bytesPerEntry;

    let text = Math.pow(2, entryBytes % 10);
    if ( entryBytes >= 40 ){
        text += " TiB";
    }
    else if ( entryBytes >= 30 ){
        text += " GiB";
    }
    else if ( entryBytes >= 20 ){
        text += " MiB";
    }
    else if ( entryBytes >= 10 ) {
        text += " KiB";
    }
    else {
        text += " B";
    }

    pageTableSizeText.html(text);
}

function updateAddresses(){
    background(0);

    updateVirtualAddress();
    updatePhysicalAddress();
    updatePageTableSize();

}

function draw(){
}