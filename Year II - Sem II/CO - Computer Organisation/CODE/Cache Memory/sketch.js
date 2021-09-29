/// -----------------------------------///
const Unit = {
    GiB : 30,
    MiB : 20,
    KiB : 10,
    B: 0
};    
                                
const AdrsUnits = { BYTE : 1, WORD : 2 };
///------------------------------------///
let address;

let mainMemorySizeInput,
    mainMemorySizeUnitInput;
let addressableUnitInput;
let wordSizeInput,
    wordSizeUnitInput;
let blockSizeInput;
let cacheSetsInput;
let cacheDataSizeInput,
    cacheDataSizeUnitInput;

let addressableUnitText;

let addressFromInput;

let tagOutput;
let indexOutput;
let blockOutput;
let wordOutput;

let tagSizeOutput;
let indexSizeOutput;
let blockSizeOutput;
let wordSizeOutput;

let totalCacheCapacityText;
let dataCacheCapacityText;

function setup(){
    createCanvas(1200, 500);
    background(0);
    fill(255)
        .strokeWeight(0)
        .textSize(20);

    /// DATA INPUT
    mainMemorySizeInput = select("#inputMainMemorySize");
    mainMemorySizeUnitInput = select("#inputMainMemorySizeUnit");
    addressableUnitInput = select("#inputAddressableUnit");
    wordSizeInput = select("#inputWordSize");
    wordSizeUnitInput = select("#inputWordSizeUnit");
    blockSizeInput = select("#inputBlockSize");
    cacheSetsInput = select("#inputCacheSets");
    cacheDataSizeInput = select("#inputCacheDataSize");
    cacheDataSizeUnitInput = select("#inputCacheDataSizeUnit");

    addressableUnitText = select("#addressableUnitOffset");

    setInputFilter(document.getElementById("inputMainMemorySize"), numFilter);
    setInputFilter(document.getElementById("inputWordSize"), numFilter);
    setInputFilter(document.getElementById("inputBlockSize"), numFilter);
    setInputFilter(document.getElementById("inputCacheDataSize"), numFilter);

    /// ADDRESS OUTPUT
    addressFromInput = select("#inputAddressFrom");
    tagOutput = select("#tagOut");
    indexOutput = select("#indexOut");
    blockOutput = select("#blockOut");
    wordOutput = select("#wordOut");

    tagSizeOutput = select("#tagSizeOut");
    indexSizeOutput = select("#indexSizeOut");
    blockSizeOutput = select("#blockSizeOut");
    wordSizeOutput = select("#wordSizeOut");
    
    setInputFilter(document.getElementById("inputAddressFrom"), hexFilter);
    
    /// CACHE CAPACITY OUTPUT
    totalCacheCapacityText = select("#totalCacheCapacityText");
    dataCacheCapacityText = select("#dataCacheCapacityText");
}

function updateCacheAddress(){
    let addressSize = Math.log2(mainMemorySizeInput.value()) + Unit[mainMemorySizeUnitInput.value()];
    let addressableUnit = AdrsUnits[addressableUnitInput.value()];
    let wordOffset = Math.log2(wordSizeInput.value() / wordSizeUnitInput.value());
    let blockOffset = Math.log2(blockSizeInput.value());
    let cacheSets = cacheSetsInput.value();
    let cacheDataSize = Math.log2(cacheDataSizeInput.value()) + Unit[cacheDataSizeUnitInput.value()];

    let blocksPerCache = cacheDataSize - (blockOffset + wordOffset);
    let index = blocksPerCache - Math.log2(cacheSets);
    let tag = addressSize - (index + blockOffset + wordOffset);

    address = new Address(tag, index, blockOffset, wordOffset, addressableUnit);

    address.print_boxes();
}

function updateCacheCapacity(){
    let lineSize = 1 + 1 + address.tag + (wordSizeInput.value() / wordSizeUnitInput.value() * 8) + 2;
    lineSize = Math.ceil(lineSize/8);

    let totalCacheCapacity = cacheSetsInput.value() * Math.pow(2, address.index) * lineSize;
    let dataCacheCapacity = cacheSetsInput.value() * Math.pow(2, address.index) * (wordSizeInput.value()  / wordSizeUnitInput.value());

    totalCacheCapacityText.html(totalCacheCapacity + " BYTES");
    dataCacheCapacityText.html(dataCacheCapacity + " BYTES");
}

function updateAddress(){
    background(0);

    updateCacheAddress();
    updateCacheCapacity();
}

function outputAddress(){
    if ( address === undefined ){
        return;
    }

    let value = addressFromInput.value();

    address.print_boxes();
    address.print_address(value);
}

function draw(){
}