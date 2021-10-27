import Page, { PrevPage, NextPage } from "./Page";

function Pagination() {
  const pages = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
  let pageMap = pages.map((page) => {
    return (
      <Page
        key={page}
        href='#'
        sym={page}
      />
    )
  });

  pageMap = [<PrevPage key={-1} href='#' />, ...pageMap, <NextPage key={0} href='#' />];

  return (
    <div className="px-4 py-3 flex items-center justify-between border-t border-gray-300">
      <div>
        <div className="text-sm text-gray-700">
          Showing{" "}
          <span className="font-medium">1</span> -{" "}
          <span className="font-medium">10</span> of{" "}
          <span className="font-medium">97</span> results
        </div>
      </div>
      <div>
        <nav className="relative z-0 inline-flex rounded-md shadow-sm -space-x-px" aria-label="Pagination">
          {pageMap}
        </nav>
      </div>
    </div>
  );
}

export default Pagination;