import { ChevronLeftIcon, ChevronRightIcon, DotsHorizontalIcon } from '@heroicons/react/solid'

interface PaginationProps {
    count: number;
    page: number;
    onPageChange: (page: number) => void;
}

interface PageProps {
    index: number | React.ReactNode;
    selected?: boolean;
    onClick?: () => void;
}

interface IconPageProps {
    onClick: () => void;
}

export default function Pagination({ count, page, onPageChange }: PaginationProps) {
    return (
        <div className="flex justify-center gap-2">
            {(page <= 1) || <PrevPage onClick={() => onPageChange(page - 1)} />}
            {createPages(count, page, onPageChange)}
            {(page >= count) || <NextPage onClick={() => onPageChange(page + 1)} />}
        </div>
    )
}

function Page({ index, selected, onClick }: PageProps) {
    if (selected) {
        return (
            <div className="flex justify-center border-purple-300 text-purple-400 items-center w-12 h-12 border-2 rounded-xl font-mono font-semibold">
                {index}
            </div>
        )
    }

    return (
        <button className="flex justify-center items-center w-12 h-12 border-2 rounded-xl font-mono font-semibold
            hover:bg-purple-100 hover:border-purple-300"
            onClick={() => onClick?.()}
        >
            {index}
        </button>
    )
}


const createPageNeighbours = (count: number, page: number, onPageChange: (page: number) => void) => {
    const pages = []
    const start = Math.max(2, page - 1)
    const end = Math.min(count - 1, page + 1)

    for (let i = start; i <= end; i++) {
        pages.push(<Page key={i} index={i} onClick={() => onPageChange(i)} selected={page === i} />)
    }

    return pages
}

const createPages = (count: number, page: number, onPageChange: (page: number) => void) => {
    const pages: React.ReactNode[] = []

    // Pagination Cases
    if (count > 5) {
        pages.push(<Page key={1} index={1} onClick={() => onPageChange(1)} selected={page === 1} />)
        if (page > 3) {
            pages.push(<Dots key={-1} />)
        }
        pages.push(createPageNeighbours(count, page, onPageChange))
        if (page < count - 2) {
            pages.push(<Dots key={-2} />)
        }
        pages.push(<Page key={count} index={count} onClick={() => onPageChange(count)} selected={page === count} />)
    }
    else {
        for (let i = 1; i <= count; i++) {
            pages.push(<Page key={i} index={i} onClick={() => onPageChange(i)} selected={page === i} />)
        }
    }

    return pages
}

const PrevPage = ({ onClick }: IconPageProps) => <Page index={<ChevronLeftIcon className="w-8" />} onClick={onClick} />

const NextPage = ({ onClick }: IconPageProps) => <Page index={<ChevronRightIcon className="w-8" />} onClick={onClick} />

const Dots = () => <Page index={<DotsHorizontalIcon className="w-8" />} />