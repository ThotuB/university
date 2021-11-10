function AuthFooter(props) {
  const { buttonClick, text, buttonText } = props;

  return (
    <div className="mt-6 text-xs font-light text-center text-gray-400">
      {text}
      <button href="#" className="font-medium text-gray-700 hover:underline"  onClick={() => buttonClick()}>
        {buttonText}
      </button>
    </div>
  );
}

export default AuthFooter;
