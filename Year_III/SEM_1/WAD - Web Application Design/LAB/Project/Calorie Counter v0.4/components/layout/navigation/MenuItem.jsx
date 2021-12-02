import Link from 'next/link';

function MenuItem(props) {
  let { svg, name, href } = props;

  return (
    <Link href={href}>
      <button className="flex items-center w-full p-3 text-sm text-gray-600 capitalize transition-colors duration-200 transform hover:bg-gray-100">
        {svg}
        <div className='mx-2'>
          {name}
        </div>
      </button>
    </Link>
  );
}

export default MenuItem;