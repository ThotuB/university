interface PaginationProps {
    count: number;
}

interface PageProps {
    index: number;
}

export default function Pagination({ count }: PaginationProps) {
    return (
        <div className="flex justify-center">
            {createPages(count)}
        </div>
    )
}

function Page({ index }: PageProps) {
    return (
        <div className="flex justify-center items-center w-12 h-12 border-2 rounded-xl">
            {index}
        </div>
    )
}


const createPages = (count: number) => {
    const pages = []
    for (let i = 0; i < count; i++) {
        pages.push(<Page index={i} />)
    }
    return pages
}