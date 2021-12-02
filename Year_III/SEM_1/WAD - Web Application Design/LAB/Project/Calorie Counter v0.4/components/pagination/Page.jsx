function Page(props) {
    const { href, sym } = props;

    return (
        <a
            href={ href }
            className="bg-white border-gray-300 text-gray-500 relative items-center px-4 py-2 border text-sm font-medium
                        hover:bg-gray-50"
        >
            { sym }
        </a>
    );
}

function PrevPage(props) {
    return (
        <Page
            href={ props.href }
            sym={
                <svg className="h-5 w-5" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path strokeLinecap="round" strokeLinejoin="round" d="M15 19l-7-7 7-7" />
                </svg>
            }
        />
    );
}

function NextPage(props) {
    return (
        <Page
            href={ props.href }
            sym={
                <svg className="h-5 w-5" fill="none" viewBox="0 0 24 24" stroke="currentColor">
                    <path strokeLinecap="round" strokeLinejoin="round" d="M9 5l7 7-7 7" />
                </svg>
            }
        />
    );
}

export default Page;
export { PrevPage, NextPage };