import Router, { useRouter } from 'next/router'
import { DotsHorizontal, ChevronLeft, ChevronRight } from '../svg/Heroicons'

function Page(props) {
    const { page, children, disabled } = props
    const router = useRouter()

    const handleClick = () => {
        const query = router.query
        query.page = page
        Router.push({
            pathname: '/food',
            query: query
        })
    }

    if (disabled) {
        return (
            <div className="bg-gray-200 border-gray-300 h-full text-gray-500 items-center px-4 py-2 border text-sm font-medium">
                {children}
            </div>
        )
    }
    return (
        <div className="bg-white border-gray-300 h-full text-gray-500 items-center px-4 py-2 border text-sm font-medium
                    hover:bg-gray-50"
            onClick={handleClick}
        >
            { children }
        </div>
    )
}

const PrevPage = ({page, disabled}) => ( 
    <Page page={page} disabled={disabled}>
        <ChevronLeft />
    </Page>
)

const NextPage = ({page, disabled}) => (
    <Page page={page} disabled={disabled}>
        <ChevronRight />
    </Page>
)

const SuspensePage = () => (
    <div className="bg-white border-gray-300 h-full text-gray-500 items-center px-4 py-2 border text-sm font-medium">
        <DotsHorizontal />
    </div>
)

export default Page
export { PrevPage, NextPage, SuspensePage }