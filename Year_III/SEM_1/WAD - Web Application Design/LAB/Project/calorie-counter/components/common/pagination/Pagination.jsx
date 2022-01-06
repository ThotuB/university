import Page, { PrevPage, NextPage, SuspensePage } from "./Page"

function Pagination(props) {
    const {pages, page, entriesPerPage, entriesTotal} = props
    const entriesFrom = entriesTotal ? (page - 1) * entriesPerPage + 1 : 0
    const entriesTo = entriesTotal ? Math.min(page * entriesPerPage, entriesTotal) : 0
    
    const pageMap = createPageMap(pages, page)

    return (
        <div className="px-4 py-3 flex items-center justify-between border-t border-gray-300">
            <div>
                <div className="text-sm text-gray-700">
                    Showing{" "}
                    <span className="font-medium">{entriesFrom}</span> -{" "}
                    <span className="font-medium">{entriesTo}</span> of{" "}
                    <span className="font-medium">{entriesTotal}</span> results
                </div>
            </div>
            <div>
                <nav className="flex shadow-sm items-center h-10">
                    {pageMap}
                </nav>
            </div>
        </div>
    )
}

function createPageMap(pages, page) {
    let pageMap = []
    
    // Pagination Cases
    if (pages > 5) {
        if (page <= 3) {
            for (let i = 1; i <= 3; i++) {
                pageMap.push(<Page key={i} page={i} disabled={(page === i)}>{i}</Page>)
            }
            pageMap.push(<SuspensePage />)
            pageMap.push(<Page key={pages} page={pages}>{pages}</Page>)
        }
        else if (page > 3 && page <= pages - 2) {
            pageMap.push(<Page key={1} page={1}>1</Page>)
            pageMap.push(<SuspensePage />)
            for (let i = page - 1; i <= page + 1; i++) {
                pageMap.push(<Page key={i} page={i} disabled={(page === i)}>{i}</Page>)
            } 
            pageMap.push(<SuspensePage />)
            pageMap.push(<Page key={pages} page={pages}>{pages}</Page>)
        }
        else if (page > pages - 2) {
            pageMap.push(<Page key={1} page={1}>1</Page>)
            pageMap.push(<SuspensePage />)
            for (let i = pages - 2; i <= pages; i++) {
                pageMap.push(<Page key={i} page={i} disabled={(page === i)}>{i}</Page>)
            }
        }
    }
    else {
        for (let i = 1; i <= pages; i++) {
            pageMap.push(<Page key={i} page={i} disabled={(page === i)}>{i}</Page>)
        }
    }

    return [
        <PrevPage key={-1} page={page-1} disabled={(page <= 1)}/>, 
        ...pageMap, 
        <NextPage key={0} page={page+1} disabled={(page >= pages)}/>
    ]
}

export default Pagination